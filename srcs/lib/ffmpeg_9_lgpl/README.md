

# FFmpeg 9 LGPL Windows 发行版

这是一个 FFmpeg 9 的 Windows LGPL 发行版，包含预编译的二进制文件、开发头文件和库文件，方便在 Windows 平台上进行多媒体处理和开发。

## 项目简介

本项目提供了 FFmpeg 9 (版本 63) 的完整 Windows 发行版，采用 LGPL 许可证。主要包含以下组件：

### 核心工具

| 工具 | 说明 |
|------|------|
| `ffmpeg.exe` | 强大的音视频转码工具，支持几乎所有格式的转换 |
| `ffplay.exe` | 基于 FFmpeg 的简单媒体播放器 |
| `ffprobe.exe` | 多媒体流分析工具，用于查看文件详细信息 |

### 运行时库

- `avcodec-63.dll` - 编解码库
- `avformat-63.dll` - 封装格式库
- `avfilter-12.dll` - 滤镜库
- `avdevice-63.dll` - 设备库
- `avutil-61.dll` - 工具库
- `swresample-7.dll` - 音频重采样库
- `swscale-10.dll` - 图像缩放库

### 开发资源

- **include/** - 完整的 C 头文件，用于二次开发
- **lib/** - 导入库 (.lib) 和模块定义文件 (.def)，支持链接到您的项目
- **presets/** - 编码预设配置

## 快速开始

### 方式一：直接使用可执行文件

1. 将 `bin/` 目录添加到系统 PATH 环境变量
2. 打开命令提示符或 PowerShell
3. 使用以下命令测试：

```bash
# 查看版本信息
ffmpeg -version

# 查看媒体文件信息
ffprobe input.mp4

# 播放媒体文件
ffplay input.mp4
```

### 方式二：添加到您的开发项目

将以下目录添加到您的项目配置中：

- **包含目录**: 添加 `include/` 到编译器的包含路径
- **库目录**: 添加 `lib/` 到链接器的库搜索路径
- **运行时**: 确保程序运行时能够找到 `bin/` 目录下的 DLL 文件

## 使用示例

### 视频转码

```bash
# 将 MP4 转换为 AVI
ffmpeg -i input.mp4 output.avi

# 提取音频
ffmpeg -i input.mp4 -vn output.mp3

# 视频格式转换
ffmpeg -i input.mkv -c:v libx264 -c:a aac output.mp4
```

### 播放媒体

```bash
# 播放视频并显示统计数据
ffplay -stats input.mp4

# 播放音频
ffplay -nodisp input.mp3
```

### 分析媒体信息

```bash
# 查看媒体文件详细信息
ffprobe -v quiet -print_format json -show_format -show_streams input.mp4
```

## 文档资源

完整的 FFmpeg 文档位于 `doc/` 目录：

| 文档 | 说明 |
|------|------|
| `ffmpeg.html` | ffmpeg 详细使用文档 |
| `ffplay.html` | ffplay 使用指南 |
| `ffprobe.html` | ffprobe 使用指南 |
| `ffmpeg-filters.html` | 滤镜使用说明 |
| `general.html` | 通用文档和架构说明 |

## 开发集成

### 使用 pkg-config

项目提供了 pkg-config 配置文件，可以通过以下方式获取编译和链接参数：

```bash
# 获取 libavcodec 的编译选项
pkg-config --cflags libavcodec

# 获取 libavcodec 的链接选项
pkg-config --libs libavcodec
```

### 链接示例

在您的 Makefile 或构建系统中添加：

```makefile
CFLAGS += -I$(FFMPEG_DIR)/include
LDFLAGS += -L$(FFMPEG_DIR)/lib

# 链接必要的库
LIBS = -lavcodec -lavformat -lavutil -lavfilter -lswscale -lswresample
```

## 系统要求

- Windows 7 或更高版本
- Visual C++ Redistributable 或 MinGW 运行环境

## 许可证

本发行版采用 **LGPL v2.1** 许可证。具体条款请参阅 `LICENSE.txt` 文件。

对于 GPL 代码（如 libx264、libx265 等），需要遵守相应的 GPL 许可证。

## 相关资源

- [FFmpeg 官方文档](https://ffmpeg.org/documentation.html)
- [FFmpeg Wiki](https://trac.ffmpeg.org/)

## 更新日志

- 初始版本：FFmpeg 9 (核心库版本 63)
- 支持 Windows 64位系统