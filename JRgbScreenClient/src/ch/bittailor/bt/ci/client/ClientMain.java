package ch.bittailor.bt.ci.client;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import ch.bittailor.bt.com.ClientConnection;
import ch.bittailor.bt.com.TcpRequestServer;
import ch.bittailor.bt.ui.RgbScreenRequestServer;
import ch.bittailor.bt.ui.VirtualRgbScreen;

public class ClientMain {

	public static void main(String[] args) {
		try {
			final VirtualRgbScreen virtualScreen = new VirtualRgbScreen(16,16);
			SwingUtilities.invokeLater(new Runnable() {
			    public void run() {
			        JFrame frame = new JFrame();
			    	frame.getContentPane().add(virtualScreen);
			    	frame.pack();
			    	frame.setVisible(true);
			    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			    }
			});
			
			RgbScreenRequestServer requestServer = new RgbScreenRequestServer(virtualScreen);
		
			ClientConnection connection;
		
			connection = new ClientConnection(new Socket("tebuildserver.nmag.ch", 8645));
			TcpRequestServer server = new TcpRequestServer(connection,requestServer);
			server.run();
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
	}
}
