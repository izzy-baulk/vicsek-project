import sys
import numpy as np
import matplotlib.pyplot as plt
import glob
import subprocess
import natsort

from matplotlib.animation import FuncAnimation

class Wrapper:
    def __init__(self, noise=0.0):
        self.noise = noise

    def run(self):
        # 1. Compile the code first
        print("Compiling C++ code...")
        compile_command = ["g++", "-g", "-std=c++17", "-o", "myvicsek", 
                            "main.cpp", "system.cpp", "particle.cpp", "box.cpp"]
        
        compilation = subprocess.run(compile_command, capture_output=True, text=True)
        
        if compilation.returncode != 0:
            print("Compilation Failed!")
            print(compilation.stderr)
            return None

        # 2. Run the newly compiled binary
        print(f"Running simulation with noise: {self.noise}")
        command = ["./myvicsek", str(self.noise)]
        result = subprocess.run(command, capture_output=True, text=True)
        return result       

def run_model():
    model = Wrapper(noise=0.1)
    model.run()

def read_config(filename, skip=2):
    """Reading an vicsek configuration from a file handle"""
    with open(filename, 'r') as file_handle:
        for i in range(skip): 
            next(file_handle)

        data = np.loadtxt(file_handle)
        conf = {}

        conf["id"] = data[:,0]
        conf["x"] = data[:,1]
        conf["y"] = data[:,2]
        conf["theta"] = data[:,3]
        conf["vx"] = np.cos(conf["theta"])
        conf["vy"] = np.sin(conf["theta"])  
        return conf

def plot(conf, ax):
    qv = ax.quiver(conf["x"], conf["y"], conf["vx"], conf["vy"], conf["theta"], scale=1, scale_units='xy', cmap='hsv')
    return qv

# function called to plot all files
def animate(i, files,qv):
    print(i)
    conf = read_config(files[i])
    pos = np.array(list(zip(conf["x"], conf["y"])))
    print(pos)
    qv.set_offsets(pos)
    qv.set_UVC(conf["vx"], conf["vy"], conf["theta"])
    return qv

def main():

    run_model()
    # files are stored in a folder
    files = glob.glob("output/*")
    if natsort:
        files = natsort.natsorted(files)
    else:
        files = sorted(files, key=lambda x: int(x.split('/')[-1]))

    # first plot
    fig, ax= plt.subplots() #

    qv = plot(read_config(files[0]),ax)
    plt.axis('equal')
    plt.axis('off')
        
    # Create the animation
    anim = FuncAnimation(fig,animate, range(len(files)), fargs=(files,qv,))
    # Show the animation
    plt.show()

main()