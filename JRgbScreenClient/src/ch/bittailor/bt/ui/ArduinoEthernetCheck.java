package ch.bittailor.bt.ui;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class ArduinoEthernetCheck {

	public static void main(String[] args) {
		for (int socketLoop = 0; socketLoop < 1000 ; socketLoop++) {
			System.out.println("Socket Loop " + socketLoop);		
			try {
				final Socket socket = new Socket("192.168.2.2",2000);
				socket.setTcpNoDelay(true);
				OutputStream outputStream = new BufferedOutputStream(socket.getOutputStream());
				for (int outerLoop = 0; outerLoop < 1000 ; outerLoop++) {
					System.out.println("Outer Loop " + outerLoop);				
					for (int connectionLoop = 0; connectionLoop < 20; connectionLoop++) {
						System.out.println("Connection Loop " + connectionLoop);
						for (int numberLoop = 0; numberLoop < 256 * 4; numberLoop++) {
							outputStream.write(numberLoop);
							if (numberLoop%6 == 0) {
								outputStream.flush();
							}
			
						}
						outputStream.flush();
						Thread.sleep(10);
					}
					Thread.sleep(4000);
				}
				outputStream.close();
				socket.close();
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	
	public static void main_A() {
		for (int socketLoop = 0; socketLoop < 1000 ; socketLoop++) {
			System.out.println("Socket Loop " + socketLoop);		
			try {
				final Socket socket = new Socket("192.168.2.2",2000);
				socket.setTcpNoDelay(true);
				OutputStream outputStream = new BufferedOutputStream(socket.getOutputStream());
				for (int connectionLoop = 0; connectionLoop < 20; connectionLoop++) {
					System.out.println("Connection Loop " + connectionLoop);
					for (int numberLoop = 0; numberLoop < 256 * 4; numberLoop++) {
						outputStream.write(numberLoop);
						if (numberLoop%6 == 0) {
							outputStream.flush();
						}
						
					}
					outputStream.flush();
					Thread.sleep(10);
				}
				outputStream.close();
				socket.close();
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
