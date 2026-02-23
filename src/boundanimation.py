import sys
import os
import platform
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import argparse

# 1. COMPILATION UTILITY
def compile_vicsek():
    arch = "x86_64" if platform.machine() == "x86_64" else "arm64"
    print(f"Compiling for {arch}...")
    
    # Get includes dynamically
    pybind_inc = subprocess.check_output([sys.executable, "-m", "pybind11", "--includes"], text=True).strip().split()
    suffix = subprocess.check_output(["python3-config", "--extension-suffix"], text=True).strip()
    
    cmd = [
        "g++", "-O3", "-Wall", "-shared", "-std=c++17", 
        "-undefined", "dynamic_lookup", "-arch", arch
    ] + pybind_inc + [
        "bindings.cpp", "particle.cpp", "system.cpp", "box.cpp",
        "-o", f"myvicsek{suffix}"
    ]
    
    subprocess.run(cmd, check=True)
    print("Compilation successful.")

# 2. RUN COMPILATION BEFORE IMPORT
compile_vicsek()
import myvicsek  # Now we can safely import

# 3. ANIMATION LOGIC
class VicsekVisualizer:
    def __init__(self, N=100, L=20.0, dt=1.0, noise=0.1):
        self.L = L
        # Initialize C++ System via Bindings
        self.system = myvicsek.System(N, L, dt, noise, 42)
        self.system.randomStart()

        # Setup Plot
        self.fig, self.ax = plt.subplots(figsize=(7, 7))
        self.ax.set_xlim(0, L)
        self.ax.set_ylim(0, L)
        
        # Initial data for quiver
        x, y, vx, vy = self.get_particle_data()
        self.qv = self.ax.quiver(x, y, vx, vy, color='royalblue', pivot='mid', scale=1, scale_units='xy')

    def get_particle_data(self):
        """Extracts data directly from C++ memory"""
        particles = self.system.particles
        x = np.array([p.x for p in particles])
        y = np.array([p.y for p in particles])
        thetas = np.array([p.theta for p in particles])
        return x, y, np.cos(thetas), np.sin(thetas)

    def update(self, frame):
        # Step the C++ simulation
        self.system.updateRule()
        
        # Pull new data
        x, y, vx, vy = self.get_particle_data()
        
        # Update Quiver plot
        self.qv.set_offsets(np.c_[x, y])
        self.qv.set_UVC(vx, vy)
        
        self.ax.set_title(f"Step: {frame}")
        return self.qv,

    def animate(self):
        # blit=True makes it much faster by only redrawing changed parts
        anim = FuncAnimation(self.fig, self.update, frames=200, interval=30, blit=True)
        plt.show()

if __name__ == "__main__":
    viz = VicsekVisualizer(N=300, L=25.0, dt=1.0, noise=0.2)
    viz.animate()