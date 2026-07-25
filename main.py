import numpy as np

# -----------------------------
# Parameters
# -----------------------------
ncols = 200
nrows = 200
cellsize = 1.0
xllcorner = 0.0
yllcorner = 0.0
nodata = -9999

# Gaussian parameters
mean_x = ncols / 2
mean_y = nrows / 2
sigma = 30.0
amplitude = 100.0

# -----------------------------
# Create coordinate grid
# -----------------------------
x = np.arange(ncols)
y = np.arange(nrows)
X, Y = np.meshgrid(x, y)

# -----------------------------
# Generate Gaussian surface
# -----------------------------
Z = amplitude * np.exp(
    -((X - mean_x)**2 + (Y - mean_y)**2) / (2 * sigma**2)
)

# -----------------------------
# Generate Gaussian distribution
# -----------------------------
xrange = np.linspace(-10, 10, 201)
Z2d = amplitude * np.exp(-((xrange - mean_x)**2  / (2 * sigma**2) ) )

# -----------------------------
# Write ESRI ASCII Grid (.qgis)
# -----------------------------
output_asc_file = "gaussian.asc"

print("len(x)", len(x))
print("len(Z2d)", len(Z2d))

with open(output_asc_file, "w") as f:
    # ESRI ASCII grids are written from the top row to the bottom
    for xi, yi in zip(xrange, Z2d[:-1]):
        f.write(f"{xi:.6f}      {yi:.6f}\n")

print(f"Gaussian surface saved to '{output_asc_file}'")
# -----------------------------
# Write ESRI ASCII Grid (.qgis)
# -----------------------------
output_surf_file = "gaussian.surf"

with open(output_surf_file, "w") as f:
    f.write(f"ncols         {ncols}\n")
    f.write(f"nrows         {nrows}\n")
    f.write(f"xllcorner     {xllcorner}\n")
    f.write(f"yllcorner     {yllcorner}\n")
    f.write(f"cellsize      {cellsize}\n")
    f.write(f"NODATA_value  {nodata}\n")

    # ESRI ASCII grids are written from the top row to the bottom
    for row in Z[::-1]:
        f.write(" ".join(f"{value:.6f}" for value in row) + "\n")

print(f"Gaussian surface saved to '{output_surf_file}'")
