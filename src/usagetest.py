import myvicsek
sys = myvicsek.System(100, 20.0, 0.1, 0.5, 42)
sys.randomStart()
sys.updateRule()

# Accessing C++ data directly in Python!
first_particle_x = sys.particles[0].x
print(f"Particle 0 is at x: {first_particle_x}")