# FFmpeg 9 LGPL Windows Distribution

This is a Windows LGPL distribution of FFmpeg 9, containing precompiled binaries, development header files, and library files, facilitating multimedia processing and development on the Windows platform.

## Project Overview

This project provides a complete Windows distribution of FFmpeg 9 (Version 63), released under the LGPL license. It mainly includes the following components:

### Core Tools

| Tool | Description |
|------|------|
| `ffmpeg.exe` | Powerful audio/video transcoding tool, supporting conversion of almost all formats |
| `ffplay.exe` | Simple media player based on FFmpeg |
| `ffprobe.exe` | Multimedia stream analysis tool, used to view detailed file information |

### Runtime Libraries

- `avcodec-63.dll` - Codec library
- `avformat-63.dll` - Container format library
- `avfilter-12.dll` - Filter library
- `avdevice-63.dll` - Device library
- `avutil-61.dll` - Utility library
- `swresample-7.dll` - Audio resampling library
- `swscale-10.dll` - Image scaling library

### Development Resources

- **include/** - Complete C header files for integration
- **lib/** - Import libraries (.lib) and module definition files (.def), supporting linking to your projects
- **presets/** - Encoding preset configurations

## Quick Start

### Method 1: Direct Executable Usage

1. Add the `bin/` directory to the system PATH environment variable
2. Open Command Prompt or PowerShell
3. Test using the following commands:

```bash
# View version information
ffmpeg -version

# View media file information
ffprobe input.mp4

# Play media file
ffplay input.mp4
```

### Method 2: Add to Your Development Project

Add the following directories to your project configuration:

- **Include Directory**: Add `include/` to the compiler's include path
- **Library Directory**: Add `lib/` to the linker's library search path
- **Runtime**: Ensure the program can find DLL files in the `bin/` directory when running

## Usage Examples

### Video Transcoding

```bash
# Convert MP4 to AVI
ffmpeg -i input.mp4 output.avi

# Extract audio
ffmpeg -i input.mp4 -vn output.mp3

# Video format conversion
ffmpeg -i input.mkv -c:v libx264 -c:a aac output.mp4
```

### Play Media

```bash
# Play video and display statistics
ffplay -stats input.mp4

# Play audio
ffplay -nodisp input.mp3
```

### Analyze Media Information

```bash
# View detailed media file information
ffprobe -v quiet -print_format json -show_format -show_streams input.mp4
```

## Documentation Resources

Complete FFmpeg documentation is located in the `doc/` directory:

| Document | Description |
|------|------|
| `ffmpeg.html` | Detailed ffmpeg usage documentation |
| `ffplay.html` | ffplay usage guide |
| `ffprobe.html` | ffprobe usage guide |
| `ffmpeg-filters.html` | Filter usage instructions |
| `general.html` | General documentation and architecture explanation |

## Development Integration

### Using pkg-config

The project provides pkg-config configuration files to obtain compilation and linking parameters via:

```bash
# Get compilation options for libavcodec
pkg-config --cflags libavcodec

# Get linking options for libavcodec
pkg-config --libs libavcodec
```

### Linking Example

Add to your Makefile or build system:

```makefile
CFLAGS += -I$(FFMPEG_DIR)/include
LDFLAGS += -L$(FFMPEG_DIR)/lib

# Link necessary libraries
LIBS = -lavcodec -lavformat -lavutil -lavfilter -lswscale -lswresample
```

## System Requirements

- Windows 7 or higher
- Visual C++ Redistributable or MinGW runtime environment

## License

This distribution is released under the **LGPL v2.1** license. Please refer to the `LICENSE.txt` file for specific terms.

For GPL code (such as libx264, libx265, etc.), the corresponding GPL license must be followed.

## Related Resources

- [FFmpeg Official Documentation](https://ffmpeg.org/documentation.html)
- [FFmpeg Wiki](https://trac.ffmpeg.org/)

## Changelog

- Initial Release: FFmpeg 9 (Core Library Version 63)
- Supports Windows 64-bit systems