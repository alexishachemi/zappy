import socket
import select
from time import time
import logging
from .vector2 import Vector2

class Net:
    def __init__(self) -> None:
        self.sock = None
        self.connected = False
        self.to_send = []
        self.to_recv = []

    def __del__(self) -> None:
        self.disconnect()

    def connect(self, host: str, port: int, team: str, wait: bool) -> tuple:
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))
        self.connected = True
        buf = self._recv()
        if buf != "WELCOME":
            raise Exception(f"Invalid welcome message (got: '{buf}')")
        login_data = self.login(team, wait)
        if login_data is None:
            raise Exception("Failed to login")
        return login_data

    def disconnect(self) -> None:
        if (not self.connected):
            return
        self.sock.close()

    def login(self, team: str, wait: bool) -> tuple | None:
        buf = None
        self.send(team)
        last_send = time()
        elapsed = 0.0
        if wait:
            logging.info("Waiting for a slot to open")
        while buf is None or (buf == "ko" and wait):
            self.update()
            buf = self.recv()
            if not wait:
                continue
            elapsed = time() - last_send
            if elapsed > 1.0 and len(self.to_recv) == 0:
                self.send(team)
                last_send = time()
        if buf == "ko":
            return None
        slots_remaining = int(buf)
        buf = self.recv()
        while buf is None:
            self.update()
            buf = self.recv()
        return slots_remaining, Vector2(*[int(x) for x in buf.split()])

    def update(self) -> None:
        if not self.connected:
            return
        if self._can_recv():
            self.to_recv += self._recv().splitlines()
        if self._can_send() and len(self.to_send) > 0:
            self._send(self.to_send.pop(0))

    def send(self, data: str) -> None:
        self.to_send.append(data)
    
    def recv(self) -> str | None:
        if len(self.to_recv) > 0:
            return self.to_recv.pop(0)
        return None

    def _send(self, data: str) -> None:
        self.sock.send((data + '\n').encode())

    def _recv(self) -> str:
        received = b''
        data = self.sock.recv(1024)
        received += data
        while len(data) == 1024:
            data = self.sock.recv(1024)
            if not data:
                break
            received += data
        received = received.decode().removesuffix('\n')
        return received

    def _can_recv(self) -> bool:
        return select.select([self.sock], [], [], 0)[0]

    def _can_send(self) -> bool:
        return select.select([], [self.sock], [], 0)[1]
