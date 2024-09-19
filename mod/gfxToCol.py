path = "mod/square.gfx.inc.c"
lines = open(path,"r",encoding="utf-8").readlines()
vtx = []
vtxOffset = 0
tris = []
rMode = -1
for line in lines:
    if line == "};\n" and rMode != -1:
        rMode = -1
        continue
    elif rMode == -1:
        if line.find("Vtx") != -1:
            rMode = 0
        elif line.find("Gfx") != -1:
            rMode = 1
        if rMode != -1:
            continue
    if rMode == 0: # Vtx
        #	{{ {805, 1087, 254}, 0, {7427, 4156}, {0, 0, 129, 255} }},
        vert = []
        lData = line.split(",")
        i = 0
        while i < 3:
            vert.append(int(lData[i].replace("{", "").replace("}", "").strip()))
            i += 1
        vtx.append(vert)
    elif rMode == 1: # Gfx
        if line.find("gsSPVertex") != -1:
            vtxOffset = int(line.split("[")[-1].split("]")[0])
        elif line.find("gsSP2Triangles") != -1:
            lData = line.split("(")[-1].split(")")[0].split(",")
            i = 0
            tri = []
            tris2 = []
            while i < 8:
                if ((i+1) % 4 == 0) and i != 0:
                    tris2.append(tri)
                    tri = []
                else:
                    tri.append(int(lData[i].strip()) + vtxOffset)
                i += 1
            tris += tris2

    pass
print(tris)

colV = []
colT = []
colS = ""
colH = ""

minx = 0.0
miny = 0.0
minz = 0.0
maxx = 0.0
maxy = 0.0
maxz = 0.0

for vertex in vtx:
    x = vertex[0]
    y = vertex[1]
    z = vertex[2]

    if x < minx:
        minx = x
    if x > maxx:
        maxx = x

    if y < miny:
        miny = y
    if y > maxy:
        maxy = y

    if z < minz:
        minz = z
    if z > maxz:
        maxz = z

    colV.append(f"{{ {x}.0, {y}.0, {z}.0 }},\n")

for tri in tris:
    one = tri[0]
    two = tri[1]
    three = tri[2]
    colT.append(f"{{ {one}, {two}, {three} }},\n")

colS = f"{{{minx}.0, {miny}.0, {minz}.0}},{{{maxx}.0, {maxy}.0, {maxz}.0}}\n"

colH = f"{len(vtx)}, {len(tris)}, &colv[0], &colt[0], &cols\n"

appendLines = ["\n", "Vec3f colv[] = {\n"]
appendLines += colV
appendLines += ["};\n", "\n", "Vec3w colt[] = {\n"]
appendLines += colT
appendLines += ["};\n", "\n", "Rect3D cols = {\n", colS]
appendLines += ["};\n", "\n", "ModelCollision colh = {\n", colH, "};\n"]

open(path, "a").writelines(appendLines)