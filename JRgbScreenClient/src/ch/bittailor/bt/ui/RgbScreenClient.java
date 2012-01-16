package ch.bittailor.bt.ui;

import java.awt.Color;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import ch.bittailor.bt.com.TcpRequestClient;

public class RgbScreenClient {

	public static void draw(IRgbScreen screen) {
		int width = screen.width();
		int height = screen.height();
		System.out.println("width = " + width);
		System.out.println("height = " + height);
		
		screen.fill(Color.BLACK);
		screen.repaint();
		
		Color colors[] = new Color[] { 
				Color.BLUE,
				Color.GREEN,
				Color.RED,
				Color.YELLOW,
				Color.CYAN};
		
		
		
		for (int i = 0; i < 5; i++) {			
			System.out.println(i);
			for (Color color : colors) {
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						screen.setPixel(x, y, color);
						
					}
				}
				screen.repaint();
			}
		}	
	}


	private static void sleep() {
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	public static void main(String[] args) {
		
		try {
			Socket socket = new Socket("192.168.2.2",2000);
			RgbScreenProxy screen = new RgbScreenProxy(new TcpRequestClient(socket));		
			draw(screen);
			
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		/*
		try {
			Socket socket = new Socket("192.168.2.2",2000);
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			
			socket.getOutputStream().write(0xAF);
			socket.getOutputStream().write(4);
			socket.getOutputStream().write(3);
			socket.getOutputStream().write(255);
			socket.getOutputStream().write(0);
			socket.getOutputStream().write(0);
			socket.getOutputStream().flush();
			
			
			socket.getOutputStream().write(0xAF);
			socket.getOutputStream().write(1);
			socket.getOutputStream().write(4);
			socket.getOutputStream().flush();
			
			socket.getOutputStream().write(0xAF);
			socket.getOutputStream().write(1);
			socket.getOutputStream().write(0);
			socket.getOutputStream().flush();
			
			System.out.println(socket.getInputStream().read());
			System.out.println(socket.getInputStream().read());
			System.out.println(socket.getInputStream().read());
			
			socket.close();
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
	}
}
