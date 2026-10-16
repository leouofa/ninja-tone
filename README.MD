# Tone Ninja

Tone Ninja is a pocket ear-training and rhythm discipline companion for the Flipper Zero. Designed for practicing musicians, vocalists, and audio enthusiasts, it pairs a silent visual metronome with a precision audio tone generator to help you develop an autonomous internal clock and acute relative pitch.

---

## Improving Musicality: The Philosophy

Musicianship relies on two foundational pillars: **rhythm** and **intonation**. Tone Ninja turns the Flipper Zero into an everyday training utility for both:

1. **Internalizing Tempo Without Auditory Crutches**: Traditional click metronomes create an acoustic crutch; when the click stops, the tempo often falters. Tone Ninja's visual metronome uses the RGB notification LED to deliver silent, peripheral tempo cues. Practicing against visual pulses trains your body to internalize time and keep steady meter without acoustic bleed into recordings or live rehearsals.
2. **Developing Pitch Recognition and Intonation Discipline**: By generating pure, steady waveforms (sine and square) across the audible spectrum (100 Hz to 2,500 Hz), Tone Ninja provides an uncolored reference for ear training, instrument tuning, and interval singing. Practicing against a steady reference tone teaches your ear to identify acoustic interference (phase beating) and lock into pitch accuracy.

---

## Structured Practice Routines

Use these structured training workflows to sharpen your timing and ear.

### 1. Silent Visual Metronome & Internal Clock Training
- **Objective**: Develop rock-solid tempo discipline using peripheral vision.
- **Workflow**:
  1. Open **Settings** and set your target **BPM** (adjustable from 5 to 200 BPM in steps of 5).
  2. Choose your **Wave Type**:
     - **Sine**: Delivers a smooth, breathing swell ideal for legato playing, vocal phrasing, and gradual meter pacing.
     - **Square**: Delivers an instant, sharp on/off flash ideal for percussive attacks, staccato articulations, and precise downbeat synchronization.
  3. Set **Light Color** (Red, Green, Blue, or All/White) to suit your lighting environment.
  4. Launch **Play** and position the Flipper Zero in your peripheral vision rather than staring directly at it.
  5. Play your instrument along with the pulses.
- **Advanced Drill (Tempo Holdout)**: Play along with the light for 4 bars, close your eyes or look away for 4 bars while maintaining the tempo, and open your eyes on bar 9 to see if your downbeat aligns perfectly with the flash.

### 2. Drone & Intonation Mastery
- **Objective**: Eliminate pitch drift and tune instruments or vocals to pure intervals.
- **Workflow**:
  1. Set the tone generator to a reference pitch (for example, Concert **A4 = 440 Hz**, **C5 = 520 Hz**, or **G4 = 390 Hz**).
  2. Start playback and adjust **Volume** to a comfortable level.
  3. Play or sing the identical unison pitch against the drone. Listen carefully for "beating" (the rhythmic pulsing caused by wave phase interference).
  4. Slowly adjust your pitch until the beating slows down and disappears completely. When the sound becomes smooth and stationary, your unison is locked.
  5. Expand the exercise to fifths, fourths, and major thirds against the drone to practice pure harmonic intervals.

#### Common Reference Frequencies (10 Hz Step Approximations)
| Note | Octave 3 | Octave 4 | Octave 5 |
| :--- | :--- | :--- | :--- |
| **C** | 130 Hz | 260 Hz | 520 Hz |
| **D** | 150 Hz | 290 Hz | 590 Hz |
| **E** | 160 Hz | 330 Hz | 660 Hz |
| **F** | 170 Hz | 350 Hz | 700 Hz |
| **G** | 190 Hz | 390 Hz | 780 Hz |
| **A** | 220 Hz | 440 Hz | 880 Hz |
| **B** | 250 Hz | 490 Hz | 990 Hz |

### 3. Blind Pitch & Interval Discrimination
- **Objective**: Train relative pitch and frequency estimation.
- **Workflow**:
  1. Start playback and look away from the screen.
  2. Press **Up** or **Down** several times to step the frequency randomly.
  3. Sing the tone you hear, name your guess for the pitch or frequency range, and check the screen.
  4. Alternatively, practice stepping up or down by specific intervals (e.g., step up 5 times = +50 Hz) and sing the target note before hitting the button.

### 4. Timbral Perception (Sine vs. Square)
- **Objective**: Train your ear to separate fundamental frequencies from upper harmonic overtones.
- **Workflow**:
  1. Set a frequency between 200 Hz and 400 Hz.
  2. Press **OK** during playback to switch between **Sine** and **Square** waves.
  3. Notice how the Sine wave sounds warm, mellow, and focused purely on the fundamental frequency, while the Square wave introduces rich, buzzy odd harmonics.

---

## App Features

- **Visual Metronome**:
  - Tempo range: **5 to 200 BPM** (configurable in increments of 5 BPM).
  - Dynamic pulse modes: **Sine** (smooth sinusoidal brightness fade) and **Square** (instant on/off flash).
  - Multi-color LED support: **Red**, **Green**, **Blue**, or **All** (white) via the Flipper Zero RGB LED.
- **Audio Tone Generator**:
  - Frequency range: **100 Hz to 2,500 Hz** (adjustable in 10 Hz increments).
  - Waveforms: Pure **Sine** wave and harmonic-rich **Square** wave.
  - Real-time animated waveform display mirroring audio playback.
  - Output volume adjustable from **0% to 100%**.
- **Live Playback Controls**: Real-time adjustment of pitch, timbre, and visual cues without interrupting practice sessions.

---

## Playback Screen Controls

While on the **Play** screen, use the hardware buttons for on-the-fly adjustments:

| Button | Action | Description |
| :--- | :--- | :--- |
| **Up** | Increase Frequency | Steps frequency up by +10 Hz |
| **Down** | Decrease Frequency | Steps frequency down by -10 Hz |
| **Left** | Previous LED Color | Cycles color backward (All &rarr; Blue &rarr; Green &rarr; Red) |
| **Right** | Next LED Color | Cycles color forward (All &rarr; Green &rarr; Blue &rarr; Red) |
| **OK** | Toggle Wave Type | Switches between Sine and Square waves (affects tone and LED pulse) |
| **Back** | Exit Playback | Stops audio and light, returns to the Main Menu |

---

## Settings Configuration

The **Settings** scene allows you to preconfigure your default session parameters:

- **Wave Type**: Choose between `Sine` or `Square`.
- **Frequency**: Set starting pitch from `100hz` to `2500hz`.
- **Volume**: Set speaker output from `0` to `100` (in steps of 10).
- **BPM**: Configure metronome tempo from `5` to `200` beats per minute.
- **Light Color**: Choose `All` (white), `Green`, `Blue`, or `Red`.

---

## Development & Building

### Dependencies

- [uFBT](https://github.com/flipperdevices/flipperzero-ufbt): Flipper Zero standalone application build tool.
- [VSCode](https://code.visualstudio.com/): Recommended for development.
- [minicom](https://en.wikipedia.org/wiki/Minicom): Recommended for serial debugging (`brew install minicom` on macOS).

### Build Commands

```bash
# Build the application
ufbt

# Build and launch on a connected Flipper Zero
ufbt launch
```

> **Note**: Ensure no other application (including qFlipper) is connected to your Flipper Zero when launching via uFBT.

### Debugging with Minicom

To view real-time debug logs:

1. Identify your Flipper Zero device port (e.g., `/dev/tty.usbmodemflip_...` on macOS).
2. Connect to the device console:
   ```bash
   minicom -D /dev/tty.usbmodemflip_YOUR_DEVICE_ID
   ```
3. In the console prompt, execute:
   ```text
   log debug
   ```
4. Launch the application to observe logs tagged with `[tone-gen]`.

---

## App Source File Structure

The application follows a modular scene architecture where scenes are self-contained and communicate through a shared app context (`src/app_context.h`):

```text
src/
├── app_context.c / .h       # Application lifecycle and view dispatcher management
├── tone_gen.c / .h          # Entry point and shared state data definitions
├── scenes/
│   ├── starting_scene.c/.h  # Main menu (Play, Settings)
│   ├── playback_scene.c/.h  # Live audio synthesis, LED timing, waveform visualization
│   └── settings_scene.c/.h  # Menu item configuration for BPM, frequency, and lights
├── system/
│   └── audio_helper.c/.h    # Low-level speaker initialization and PWM tone generation
└── utils/
    └── linked_list.c/.h     # Linked list helper data structure
```

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
