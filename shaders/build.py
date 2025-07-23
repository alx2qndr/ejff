import os
import glob
import subprocess

output_dirs = ["bin/spv", "bin/msl", "bin/dxil"]
for dir in output_dirs:
    os.makedirs(dir, exist_ok=True)

def compile_shaders(extension):
    for filename in glob.glob(f"src/*.{extension}.hlsl"):
        if os.path.isfile(filename):
            base = filename.replace(".hlsl", "")
            base_name = os.path.basename(base)
            subprocess.run(["shadercross", filename, "-o", f"bin/spv/{base_name}.spv"])
            subprocess.run(["shadercross", filename, "-o", f"bin/msl/{base_name}.msl"])
            subprocess.run(["shadercross", filename, "-o", f"bin/dxil/{base_name}.dxil"])

for ext in ["vert", "frag", "comp"]:
    compile_shaders(ext)
