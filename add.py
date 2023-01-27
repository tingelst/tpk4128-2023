import ctypes
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
dll_file = os.path.join(dir_path + "/build", "libadd.so")

lib = ctypes.CDLL(dll_file)


def main():
    print(lib.add_two_ints(1, 2))


if __name__ == "__main__":
    main()
