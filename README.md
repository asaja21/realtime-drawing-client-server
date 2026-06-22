# Realtime Drawing Client-Server

A distributed drawing application built with **Qt** (server) and **MFC** (client), developed as part of the AD-IHM course at Polytech Paris-Saclay (EIE5, 2024).

## Overview

The server (Qt) captures mouse drawing events and broadcasts each line segment in real time to all connected clients. Each client (MFC) renders the received segments using either GDI or GDI+ rendering, switchable at runtime.

## Architecture

DrawServer (Qt)              DrawClient (MFC)

─────────────────            ─────────────────

QTcpServer : 4040 port       Winsock / CAsyncSocket

Mouse capture (QChildView)   GDI / GDI+ rendering

Non-persistent rendering     Non-persistent rendering

Broadcast to N clients       Connection state management

## Features

- **Server (Qt)**
  - Custom `QChildView` widget with asynchronous repaint
  - TCP server supporting up to 50 simultaneous clients
  - Menu-driven connection management

- **Client (MFC)**
  - SDI application with dynamic GDI/GDI+ switching
  - Custom `PathGradientBrush` rendering in GDI+ mode
  - Robust connection/disconnection handling with reconnection support

## Technologies

- C++ / MFC / Qt 4.8.7
- TCP/IP sockets (Qt Network, Winsock)
- GDI / GDI+ (Gdiplus)
- Visual Studio 2008 (VS9)

## Build

This project was developed and tested with **Visual Studio 2008** and **Qt 4.8.7**.

- `DrawServer` requires the Qt 4.8.7 Visual Studio Add-in
- `DrawClient` requires MFC support (Visual Studio Professional/Enterprise edition)

> Precompiled executables are available in the [Releases](../../releases) section for direct testing without building from source.

## Project Context

Developed for the AD-IHM exam (Applications Distribuées — Interface Homme-Machine), EIE5, Polytech Paris-Saclay.