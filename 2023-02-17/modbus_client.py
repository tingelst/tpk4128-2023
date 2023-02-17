import socket
import struct

from dataclasses import dataclass

HOST = "192.168.250.12"
PORT = 502

transaction = 0x0001
identifier = 0x0000
length = 0x0006
unitid = 0x00
fcode = 0x03  # Holding register fcode.
reg_addr = 0x07D0  # Register address.
count = 0x0002  # Read two registers
crc = 0xC5CE

packed = struct.pack(
    ">HHHBBHH", transaction, identifier, length, unitid, fcode, reg_addr, count
)

transaction = 0x0001
identifier = 0x0000
length = 0x0006
unitid = 0x11
fcode = 0x03  # Holding register fcode.
reg_addr = 0x006B  # Register address.
count = 0x0003  # Read three register.


total_pack_string = "0x{:04x}{:04x}{:04x}{:02x}{:02x}{:04x}{:04x}".format(
    transaction, identifier, length, unitid, fcode, reg_addr, count
)
print(total_pack_string)
total_pack_hex = hex(int(total_pack_string, 16))
print(total_pack_hex)


def create_activation_request():
    transaction = 0x0001
    identifier = 0x0000
    length = 0x001A
    unitid = hex(9)
    fcode = 0x10  # Holding register fcode.
    reg_addr = 0x03E8  # Register address.
    count = 0x06
    data = b"x00\x00\x00\x00\x00\x00"

    header = struct.pack()

    crc = b"0x7330"
    packed = (
        struct.pack(
            ">HHHBBHH", transaction, identifier, length, unitid, fcode, reg_addr, count
        )
        + data
    )

    return packed + data + crc


@dataclass
class Header:
    transaction: int
    protocol: int
    length: int
    unitid: int


def to_hex(num: int):
    return int(hex())


def close_gripper():
    transaction = 8
    identifier = 0
    length = 13
    unitid = 0
    fcode = 16
    reg_addr = 0
    word_count = 3
    num_bytes = 6
    action_request = 9
    gripper_options = 0
    gripper_options2 = 0
    position_request = 100
    speed = 25
    force = 255
    crc = 16937

    data = struct.pack(
        ">HHHBBHHBBBBBBBH",
        transaction,
        identifier,
        length,
        unitid,
        fcode,
        reg_addr,
        word_count,
        num_bytes,
        action_request,
        gripper_options,
        gripper_options2,
        position_request,
        speed,
        force,
        crc,
    )

    return data




data = close_gripper()

print(data)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    s.sendall(data)
    data = s.recv(1024)
    print(f"Received {data!r}")
