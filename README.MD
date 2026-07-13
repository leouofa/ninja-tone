# Tone Ninja

This repo contains Tone Ninja, a Flipper Zero companion app for Ninja Roll. The app currently provides tone playback, combined tone/light settings, and an instructions screen stubbed in for future work. It is written entirely in C.

## Dependencies

This project depends on [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) for building. It is also recommended to install VSCode for ease of development, as well as [minicom](https://en.wikipedia.org/wiki/Minicom) for debugging (`brew install minicom`).

## App Source File Structure

The application is structured such that each scene can be self contained, with the sharing of data between scenes done via the app context. All of the scenes can be found with their corresponding source and header files in the `src/scenes` directory. The scenes do as follows:

- **Starting Scene**: The scene where the application starts. This shows the main menu options: Play, Settings, and Instructions.
- **Playback Scene**: The Play screen where the sound is played. Animates a waveform with the *approximate* shape of the sound being played.
- **Settings Scene**: The Settings screen where users can configure tone and light properties.
- **Instructions Scene**: A blank placeholder screen for future app instructions.

Note as well that the app context file is generic, and designed in such as way that it should not need to be updated for things specific to the application. This allows for an easier time to allow scenes to self manage, insteaed of having somewhere else that centrally manages everything.

## Helpful Commands

- `ufbt`: Builds the project
- `ufbt launch`: Launches the project on a device. Make sure no other applications (including qFlipper) are connected to the device.
- `minicom -D /dev/tty.X`: Replace `X` with the name of your flipper device when connected and then use this to start a command line interface to your flipper device. From there, you can run `log debug` to see debug logs from the app while it is running.
