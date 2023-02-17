import struct

transaction = 0x0001
identifier = 0x0000
length = 0x0006
unitid = 0x11
fcode = 0x03  # Holding register fcode.
reg_addr = 0x006B  # Register address.
count = 0x0003  # Read three register.


total_pack_string = '0x{:04x}{:04x}{:04x}{:02x}{:02x}{:04x}{:04x}'.format(
    transaction, identifier, length, unitid, fcode, reg_addr, count
)
total_pack_hex = hex(int(total_pack_string, 16))

'''Or with using pack method.'''
pack_ = struct.pack(
   '>HHHBBHH', transaction, identifier, length, unitid, fcode, reg_addr, count
)

# Then send the pack_ or total_pack_hex using a TCP-Socket.
