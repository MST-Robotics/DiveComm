#!/bin/python3
'''
ControlStation is a class designed to be used to communicate with
the wrist-computer of an auxilliary diver for the Missouri University of Science and Technology
Underwater Robotics Team
'''
import socket

class ControlStation():
    def __init__(self):
        # setup
        self.target_ip = '127.0.0.1'  # tether should broadcast wifi that we can hook to
        self.sock = None
        self.buf_size = 255  # number of bytes in cmd

    def __enter__(self):
        self.sock = socket.socket()  # Initialize new socket
        self.sock.settimeout(3)  # only wait 3 seconds for response from wrist-computer
        self.sock.connect(self.target_ip)
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.sock.close()  # ensure sockets are closed in the event of failure

    def read(self):
        try:
            data = self.sock.recv(self.buf_size)
            return data
        except socket.timeout:
            return '!! ~NO RESPONSE FROM DIVER~ !!'

    def send(self, msg):
        'Send given message (str) to the diver'
        self.sock.sendto(bytes(msg), (self.target_ip, self.target_port))

    def eval(self, msg):
        '''
        Evaluate given message (str) and determine what the appropriate action is

        Note: This is where all command parsing happens, and will likely be the
              meatiest area.
        '''
        if msg[0] == '\\':
            raise NotImplementedError('base-station commands must still be written')
        else:  # Not a base-station command
            return msg

    def run(self):
        'Spin up a simple REPL for interacting with remote system'
        while True:
            self.send(self.eval(input('~> ')))
            print(self.read())


if __name__ == '__main__':
    with ControlStation() as station:
        station.run()
