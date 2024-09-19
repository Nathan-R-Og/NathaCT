from glob import glob

def yamlEdit(yaml):
    lines = open(yaml, "r", encoding="utf-8").readlines()
    minus = yaml.find("copy") != -1

    i = 0
    while i < len(lines):
        line = lines[i]
        if line.find("type: collision") != -1 and line.find('data_only: True') == -1:
            lines[i] = line.replace("}", ", data_only: True}")
        if minus and line.find("type: collision") != -1 and line.find("Header") != -1:
            addr = line.split("start: ")[-1].split(", ")[0]
            spaces = line.split("-")[0]
            lines[i] = f"{spaces}- [{addr}] #header\n"
        if minus and line.find("animPointers") != -1:
            addr = line.split("[")[-1].split(", ")[0]
            spaces = line.split("-")[0]
            lines[i] = f"{spaces}- [{addr}] #animPointers\n"
        
        if (line.find("gfxSeg,") != -1 or\
           line.find("vtx,") != -1 or\
           line.find("animArray,") != -1 or\
           line.find("lights,") != -1 or\
           line.find("animHeader,") != -1)\
              and line.find(":") == -1:
            
            args = line.split("[")[-1].split("]")[0].split(", ")
            spaces = line.split("-")[0]
            lines[i] = spaces+f"- {{start: {args[0]}, type: {args[1]}, name: {args[2]}, data_only: True}}\n"
            if line.find("animArray,") != -1:
                lines[i] = spaces+f"- {{start: {args[0]}, type: {args[1]}, name: {args[2]}, frames: {args[3]}, objects: {args[4]}, data_only: True}}\n"

        i += 1
    open(yaml, "w", encoding="utf-8").writelines(lines)

yamlEdit("chameleontwist.jp.copy.yaml")
yamlEdit("chameleontwist.jp.yaml")

def getSymbol(file, fix = True):
    lines = open(file, "r", encoding="utf-8").readlines()
    for line in lines:
        if line.find(" = ") != -1:
            if fix:
                return fixSymbol(line)
            else:
                return line

def fixSymbol(symbol):
    if symbol.find("[") == -1: return symbol

    first = symbol.split("[")[0]
    second = symbol.split("]")[-1]
    return first+"[]"+second

fixThing = True
def cEdit(c):
    lines = open(c, "r", encoding="utf-8").readlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        array = line.find("RoomObject") != -1 or\
                line.find("RoomActor") != -1 or\
                line.find("SpriteActor") != -1 or\
                line.find("Collectable") != -1 or\
                line.find("RoomInstance") != -1
        needsInnie = (line.find(".gfx.inc.c") != -1 and lines[i-1].find("Gfx ") == -1) or\
                     (line.find(".vtx.inc.c") != -1 and lines[i-1].find("Vtx ") == -1) or\
                     (line.find(".animArr.inc.c") != -1 and lines[i-1].find("Mtx ") == -1) or\
                     (line.find(".animH.inc.c") != -1 and lines[i-1].find("Anim ") == -1) or\
                     (line.find(".colV.inc.c") != -1 and lines[i-1].find("Vec3f ") == -1) or\
                     (line.find(".colT.inc.c") != -1 and lines[i-1].find("Vec3w ") == -1) or\
                     (line.find(".colS.inc.c") != -1 and lines[i-1].find("Rect3D ") == -1) or\
                     (line.find(".light.inc.c") != -1 and lines[i-1].find("Lights1 ") == -1)
        fullInnie = line.find(".animP.inc.c") != -1
                     
        if array and line.find(" = {") != -1 and fixThing:
            typer = ""
            if line.find("RoomObject") != -1:
                typer = "RoomObject"
            elif line.find("RoomActor") != -1:
                typer = "RoomActor"
            elif line.find("SpriteActor") != -1:
                typer = "SpriteActor"
            elif line.find("Collectable") != -1:
                typer = "Collectable"
            elif line.find("RoomInstance") != -1:
                typer = "RoomInstance"


            #get rid of the size dimension. lame.
            first = line.split("[")[0]
            second = line.split("]")[-1]
            lines[i] = first+"[]"+second
            actualLines = []
            oi = i
            while line.find("};") == -1:
                i += 1
                line = lines[i]
                actualLines.append(line)
            actualLines.pop(-1)
            oi += 1

            comments = []
            properArgs = []
            for roomLine in actualLines:
                comment = ''
                roomObject = roomLine.split(",")
                if roomLine.find("//") != -1:
                    comment = " "+("//"+roomLine.split("//")[-1]).strip()
                    roomObject = roomLine.split("//")[0].split(",")

                if typer == "RoomObject":
                    position = (",".join([roomObject.pop(0), roomObject.pop(0), roomObject.pop(0)])).strip()
                    scale = (",".join([roomObject.pop(0), roomObject.pop(0), roomObject.pop(0)])).strip()
                    roomObject.insert(0, position)
                    roomObject.insert(1, scale)
                elif typer == "RoomActor":
                    position = (",".join([roomObject.pop(1), roomObject.pop(1), roomObject.pop(1)])).strip()
                    roomObject.insert(1, position)
                elif typer == "SpriteActor":
                    smth = (",".join([roomObject.pop(2), roomObject.pop(2), roomObject.pop(2)])).strip()
                    roomObject.insert(2, smth)
                    smth2 = (",".join([roomObject.pop(3), roomObject.pop(3), roomObject.pop(3)])).strip()
                    roomObject.insert(3, smth2)
                    smth3 = (",".join([roomObject.pop(12), roomObject.pop(12), roomObject.pop(12)])).strip()
                    roomObject.insert(12, smth3)
                elif typer == "Collectable":
                    position = (",".join([roomObject.pop(1), roomObject.pop(1), roomObject.pop(1)])).strip()
                    roomObject.insert(1, position)



                x = 0
                while x < len(roomObject):
                    roomObject[x] = roomObject[x].strip()
                    if roomObject[x] in ["}", ""]:
                        roomObject.pop(x)
                        x -= 1
                    x += 1

                if roomObject[0][:1] == "{":
                    roomObject[0] = roomObject[0][1:]
                if roomObject[-1][-1:] == "}":
                    roomObject[-1] = roomObject[-1][:-1]

                x = 0
                while x < len(roomObject):
                    roomObject[x] = roomObject[x].strip()
                    if roomObject[x] in ["}", ""]:
                        roomObject.pop(x)
                        x -= 1
                    x += 1

                properArgs.append(roomObject)
                comments.append(comment)

            argSpaces = []
            for args in properArgs:
                x = 0
                while x < len(args):
                    arg = args[x]
                    arglen = len(str(arg))
                    if x >= len(argSpaces):
                        argSpaces.append(arglen)
                    else:
                        if arglen > argSpaces[x]:
                            argSpaces[x] = arglen
                    x += 1
            
            reconstructions = []
            al = 0
            while al < len(properArgs):
                args = properArgs[al]
                newLine = ""
                x = 0
                while x < len(args):
                    arg = args[x]
                    diff = argSpaces[x] - len(arg)
                    add = str(arg)
                    for l in range(diff+1):
                        add = " "+add
                    newLine += add
                    if x < len(args)-1:
                        newLine += ","
                    x += 1
                actualNewLine = f"    {{{newLine}}}"
                if al < len(properArgs)-1:
                    actualNewLine+=","
                actualNewLine += comments[al]
                actualNewLine += "\n"
                reconstructions.append(actualNewLine)
                al += 1

            for line in reconstructions:
                lines[oi] = line
                oi += 1
        elif needsInnie:
            file = line.split('#include "')[-1].split('"')[0]
            if line.find("animArr") != -1:
                symbol = getSymbol(file, False)
            else:
                symbol = getSymbol(file)
            if line.find(".light.inc.c") != -1:
                symbol = symbol.replace("{", "")
            lines.insert(i, symbol)
            lines[i+1] = line.replace("#", "    #")
            if line.find(".light.inc.c") == -1:
                lines.insert(i+2, "};\n")

            i+=2
        elif fullInnie:
            file = line.split('#include "')[-1].split('"')[0]
            liners = open(file, "r", encoding="utf-8").readlines()
            reading = False
            x = 0
            lines.pop(i)
            takies = []
            while x < len(liners):
                liner = liners[x]
                if not reading and liner.find(" = ") != -1:
                    liners[x] = fixSymbol(liners[x])
                    reading = True
                if reading:
                    takies.append(liner)
                    if liner.find("};") != -1:
                        break
                x += 1
            takies.reverse()
            while len(takies) > 0:
                lines.insert(i, takies.pop(0))



                
        i += 1
    open(c, "w", encoding="utf-8").writelines(lines)

for c in glob("src/**/*.c"):
    cEdit(c)