# Power and Battery Safety

The project has been described as using three 3.7 V Li-ion cells and an MT306 boost converter. The exact cell arrangement and converter board limits are not yet verified. **Do not connect the battery pack to the Arduino until these are confirmed.**

## Important voltage facts

- A single Li-ion cell is about 3.6–3.7 V nominal and up to 4.2 V when fully charged.
- Three cells in series (3S) are about 11.1 V nominal and 12.6 V fully charged.
- Three cells in parallel (1S3P) remain about 3.6–3.7 V nominal and up to 4.2 V fully charged.
- A boost converter raises voltage; a boost-only board does not step a 3S pack down to 5 V.
- A board marked MT3608 is commonly a boost converter. The marking and datasheet for the actual board must be checked; do not assume MT306 and MT3608 are interchangeable.

## Safe power procedure

1. Identify whether the cells are in series or parallel by inspecting the holder/wiring.
2. Identify the exact converter model and its permitted input voltage/current.
3. Use a suitable battery protection/BMS and charger for the actual cell configuration.
4. With the Arduino disconnected, measure converter output using a multimeter.
5. Adjust and verify a stable 5.0 V output before connecting compatible 5 V loads.
6. Connect the regulated supply to the Arduino using the correct input path for the board and keep all circuit grounds common.
7. Check current capacity and heat under load.

Do not:
- Apply an 11.1–12.6 V 3S pack to a boost-only converter and expect 5 V output.
- Feed an unregulated battery directly into the Arduino 5V pin.
- Mix cells of different chemistry, age, capacity, or state of charge in one pack.
- Charge Li-ion cells without a charger designed for the pack configuration.
- Leave an unprotected Li-ion pack unattended during testing.

For initial development, powering the UNO by USB is the simplest option. Add the battery system only after the converter output and protection arrangement are verified.
