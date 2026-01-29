import time
import dv_processing as dv

# ================================
# USER INPUT
# ================================
filename = input("Enter output filename (without extension): ").strip()
if filename == "":
    filename = "recording"

duration = 60.0

output_path = f"{filename}.aedat4"
print(f"\nOutput file: {output_path}")
print(f"Recording for {duration} seconds...\n")

# ================================
# OPEN CAMERA
# ================================
capture = dv.io.camera.open()
resolution = capture.getEventResolution()


# Configure writer (event-only)
config = dv.io.MonoCameraWriter.EventOnlyConfig(filename, resolution)
writer = dv.io.MonoCameraWriter(output_path, config)

# ================================
# RECORD LOOP
# ================================
start_time = time.time()

try:
    while capture.isRunning():
        # Stop after duration
        if time.time() - start_time >= duration:
            print("\nTime limit reached. Stopping recording...")
            break

        events = capture.getNextEventBatch()
        if events is not None:
            writer.writeEvents(events)
        else:
            time.sleep(0.001)

except KeyboardInterrupt:
    print("\nRecording interrupted by user.")

finally:
    del writer
    del capture
    print(f"Recording saved to: {output_path}")
