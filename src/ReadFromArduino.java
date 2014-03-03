/**
 * @version     1.0                 (current version number of program)
 * @since     25 Feb 2014
 * This program has been modified by xyz.
 */
// March 2014 - xyz - Modified the code to implement the  abc feature
//replace xyz with your name and abc with the name of feature

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

public class ReadFromArduino {
	static InputStream input;
	static OutputStream output;

	// This function will read value from serial port and print on console
	public static void readAndPrintSerialPortValue() throws Exception {
		// for linux
		// CommPortIdentifier.getPortIdentifier("/dev/ttyACM3");

		// for windows
		// replace COM3 with correct port number, It could be COM4 or COM5.
		CommPortIdentifier portId = CommPortIdentifier
				.getPortIdentifier("COM3");

		SerialPort port = (SerialPort) portId.open("serial talk", 4000);
		input = port.getInputStream();
		port.setSerialPortParams(9600, SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

		while (true) {
			if (input.available() > 0) {
				System.out.print((char) (input.read()));
			}
		}

	}
}
