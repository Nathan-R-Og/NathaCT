import os
import subprocess

dir_path = 'src/'
asm_path = 'asm/'
assets_path = 'assets/'
cflags = '-G 0 -fullwarn -verbose -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul'

header = (
    "AS = mips-linux-gnu-as\n"
    "CPP = cpp\n"
    "LD = mips-linux-gnu-ld\n"
    "OBJDUMP = mips-linux-gnu-objdump\n"
    "OBJCOPY = mips-linux-gnu-objcopy\n"
    "OBJCOPYFLAGS = -O binary\n"
    "PYTHON = python3\n"
    "cflags = -G 0 -fullwarn -verbose -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul\n"
    "include_cflags = -I. -Iinclude -Iinclude/PR -Iassets -Isrc\n"
    "check_warnings_gcc = -Wall -Waddress -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion -Wno-comment\n"
    "cc_check = gcc -fsyntax-only -fno-builtin -fsigned-char -std=gnu90 -m32 $check_warnings_gcc $include_cflags\n"
    "ido_cc = tools/ido_5.3/usr/lib/cc\n"
    "mips_version = -mips2\n"
    "DEFINES = -D_LANGUAGE_C -DF3DEX_GBI -DNDEBUG\n"
    "CFLAGS = -woff 649,838 $include_cflags\n"
    "ASM_PROC = python3 tools/asm-processor/build.py\n"
    "ASM_PROC_FLAGS = --input-enc=utf-8 --output-enc=euc-jp\n"
    "ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -Iinclude -Isrc\n"
    "opt_flags = -O2\n"
    "objdump_command = $OBJDUMP $in > $in:.o=.s\n"
    "splat = python3 tools/splat/split.py chameleontwist.jp.yaml\n"
    "XGCC = mips-linux-gnu-gcc\n"
    "IMG_CONVERT = tools/image_converter.py\n"
    "GCC_FLAGS = $include_cflags $DEFINES -G 0 -mno-shared -march=vr4300 -mfix4300 -mabi=32 -mhard-float -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra -Wno-missing-braces"
    "\n"

    "rule audio_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O2 -o $out $in\n"
    "\n"

    "rule code_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O2 -o $out $in\n"
    "\n"

    "rule gu_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O2 -o $out $in\n"
    "\n"

    "rule io_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O1 -o $out $in\n"
    "\n"

    "rule libc_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O2 -o $out $in\n"
    "\n"

    "rule libc_ll_cc\n"
    "  command = ($ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS -mips3 -32 -O1 -o $out $in) && (python3 tools/set_o32abi_bit.py $out)\n"
    "  description = Generating object file and setting o32abi bit for $out\n"
    "\n"

    "rule xprintf_cc\n"
    "  command = $ido_cc -c $CFLAGS $mips_version -O3 -o $out $in \n"
    "\n"

    "rule o32_abi_set\n"
    "  command = python3 tools/set_o32abi_bit.py build/libc/ll.c.o"
    "\n"

    "rule os_cc\n"
    "  command = $ASM_PROC $ASM_PROC_FLAGS $ido_cc -- $AS $ASFLAGS -- -c $cflags $DEFINES $CFLAGS $mips_version -O1 -o $out $in\n"
    "\n"

    "rule s_file\n"
    "  command = iconv --from UTF-8 --to EUC-JP $in | $AS $ASFLAGS -o $out\n"
    "\n"

    "rule bin_file\n"
    "  command = $LD -r -b binary -o $out $in\n"
    "\n"

    "rule data_cc\n"
    " command = $XGCC -c $GCC_FLAGS -o $out $in\n"
    "\n"
    
    "rule ci8_img_cc\n"
    " command = python3 ./$IMG_CONVERT ci8 $in $out\n"
    "\n"

    "rule ia8_img_cc\n"
    " command = python3 ./$IMG_CONVERT ia8 $in $out\n"
    "\n"

    "rule ia4_img_cc\n"
    " command = python3 ./$IMG_CONVERT ia4 $in $out\n"
    "\n"

    "rule rgba32_img_cc\n"
    " command = python3 ./$IMG_CONVERT rgba32 $in $out\n"
    "\n"

    "rule rgba16_img_cc\n"
    " command = python3 ./$IMG_CONVERT rgba16 $in $out\n"
    "\n"

    "rule ci4_img_cc\n"
    " command = python3 ./$IMG_CONVERT ci4 $in $out\n"
    "\n"

    "rule pal_cc\n"
    " command = python3 ./$IMG_CONVERT palette $in $out\n"
    "\n"

    "rule j_to_png_bin\n"
    " command = ($LD -r -b binary -o $out $in) && (rm -f $in)\n"
    "\n"

    "rule make_elf\n"
    "  command = mips-linux-gnu-ld -T chameleontwist.jp.ld -T undefined_syms_auto.txt -Map build/chameleontwist.jp.map --no-check-sections -o $out\n"
    "\n"

    "rule make_rom_bin\n"
    "  command = mips-linux-gnu-objcopy -O binary $in $out\n"
    "\n"

    "rule make_rom_z64\n"
    "  command = (cp $in $out) && (sha1sum -c chameleontwist.jp.sha1)\n"
    "\n"
)

# Traverse each subdirectory recursively and find all C files
def append_extension(filename):
    return filename + '.o'

c_files = []
for root, dirs, files in os.walk(dir_path):
    for file in files:
        if file.endswith('.c'):
            c_files.append(os.path.join(root, file))

s_files = []
for root, dirs, files in os.walk(asm_path):
    for file in files:
        if file.endswith('.s'):
            s_files.append(os.path.join(root, file))

bin_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('.bin'):
            bin_files.append(os.path.join(root, file))

rgba32_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('rgba32.png'):
            rgba32_files.append(os.path.join(root, file))

rgba16_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('rgba16.png'):
            rgba16_files.append(os.path.join(root, file))

ia8_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('ia8.png'):
            ia8_files.append(os.path.join(root, file))

ia4_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('ia4.png'):
            ia4_files.append(os.path.join(root, file))

ci8_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('ci8.png'):
            ci8_files.append(os.path.join(root, file))

ci4_files = []
for root, dirs, files in os.walk(assets_path):
    for file in files:
        if file.endswith('ci4.png'):
            ci4_files.append(os.path.join(root, file))

pal_files = []
pal_files.extend([f.replace('.png', '.pal') for f in ci8_files])
pal_files.extend([f.replace('.png', '.pal') for f in ci4_files])

j_files = []
j_files.extend([f.replace('.png', '.j') for f in rgba32_files])
j_files.extend([f.replace('.png', '.j') for f in rgba16_files])
j_files.extend([f.replace('.png', '.j') for f in ia8_files])
j_files.extend([f.replace('.png', '.j') for f in ia4_files])
j_files.extend([f.replace('.png', '.j') for f in ci8_files])
j_files.extend([f.replace('.png', '.j') for f in ci4_files])

# Combine the lists and change file extensions
o_files = []
for file in c_files + s_files + bin_files + rgba32_files + rgba16_files + ia8_files + ia4_files + ci4_files + ci8_files:
    if 'src/mod/' not in file and not file.startswith('src/mod/'):
        if 'asm/nonmatchings/' not in file:
            o_files.append("build/" + append_extension(file))

with open('build.ninja', 'w') as f:
    f.write(header)

# Write the full path of each C file to a new text file called build.ninja
with open('build.ninja', 'a') as outfile:
    # Write the rules for the .c files
    for c_file in c_files:
        if "src/mod" in os.path.relpath(c_file):
            continue
        else:
            if os.path.basename(c_file) == "ll.c":
                outfile.write("build build/" + os.path.splitext(c_file)[0] + ".c.o: " + "libc_ll_cc " + c_file + "\n")
            else:
                folder_name = os.path.basename(os.path.dirname(c_file))
                if folder_name == "mod":
                    continue # skip over the file
                outfile.write("build build/" + os.path.splitext(c_file)[0] + ".c.o: " + folder_name + "_cc " + c_file + "\n")


    # Write the rules for the .s files
    for s_file in s_files:
        if "asm/nonmatchings" in s_file:
            continue
        outfile.write("build build/" + os.path.splitext(s_file)[0] + ".s.o: " + "s_file " + s_file + "\n")

    # Write the rules for the .bin files
    for bin_file in bin_files:
        outfile.write("build build/" + os.path.splitext(bin_file)[0] + ".bin.o: " + "bin_file " + bin_file + "\n")

    # Write the rules for ia8 files
    for ia8_file in ia8_files:
        outfile.write("build " + os.path.splitext(ia8_file)[0] + ".j: " + "ia8_img_cc " + ia8_file + "\n")

    # Write the rules for ia4 files
    for ia4_file in ia4_files:
        outfile.write("build " + os.path.splitext(ia4_file)[0] + ".j: " + "ia4_img_cc " + ia4_file + "\n")

    # Write the rules for rgba32 files
    for rgba32_file in rgba32_files:
        outfile.write("build " + os.path.splitext(rgba32_file)[0] + ".j: " + "rgba32_img_cc " + rgba32_file + "\n")

    # Write the rules for rgba16 files
    for rgba16_file in rgba16_files:
        outfile.write("build " + os.path.splitext(rgba16_file)[0] + ".j: " + "rgba16_img_cc " + rgba16_file + "\n")
    
    # Write the rules for ci8 files
    for ci8_file in ci8_files:
        outfile.write("build " + os.path.splitext(ci8_file)[0] + ".j: " + "ci8_img_cc " + ci8_file + "\n")

    # Write the rules for ci8 pal files
    for ci8_file in ci8_files:
        outfile.write("build " + os.path.splitext(ci8_file)[0] + ".pal.j: " + "pal_cc " + ci8_file + "\n")

    # Write the rules for ci4 files
    for ci4_file in ci4_files:
        outfile.write("build " + os.path.splitext(ci4_file)[0] + ".j: " + "ci4_img_cc " + ci4_file + "\n")

    # Write the rules for ci4 pal files
    for ci4_file in ci4_files:
        outfile.write("build " + os.path.splitext(ci4_file)[0] + ".pal.j: " + "pal_cc " + ci4_file + "\n")

    # Write the rules for ci4 files
    for pal_file in pal_files:
        outfile.write("build build/" + os.path.splitext(pal_file)[0] + ".pal.o: " + "j_to_png_bin " + pal_file + ".j " + "\n")

    #j files are png images converted using image_converter.py
    for j_file in j_files:
        if not file.endswith('.pal.j'):
            outfile.write("build build/" + os.path.splitext(j_file)[0] + ".png.o: " + "j_to_png_bin " + j_file + "\n")



    # Build the ninja rule with the .o files
    outfile.write("build build/chameleontwist.jp.elf: make_elf " + " ".join(o_files) + "\n")
    outfile.write("build build/chameleontwist.jp.bin: make_rom_bin build/chameleontwist.jp.elf\n")
    outfile.write("build build/chameleontwist.jp.z64: make_rom_z64 build/chameleontwist.jp.bin\n")
