package ch.bittailor.bt.ui;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import ch.bittailor.bt.com.ClientConnection;
import ch.bittailor.bt.com.TcpRequestClient;

public class RgbScreenServer {
	
	private ServerSocket mServer;
	private Thread mServerThread;
	private IRgbScreenRepository mRepository;
	
	public RgbScreenServer(int iPort, IRgbScreenRepository iRepository) throws IOException{
		mServer = new ServerSocket(iPort);	
		mRepository = iRepository;
	}
	
	public void start() {
		mServerThread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				workcycle();
			}
		});
		mServerThread.start();
	}
	
	public void stop() {		
		try {
			mServerThread.interrupt();
			mServerThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		try {
			mServer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void workcycle() {
		while (true) {
			try {
				Socket client = mServer.accept();
				TcpRequestClient requestClient = new TcpRequestClient(new ClientConnection(client));
				RgbScreenProxy proxy = new RgbScreenProxy(requestClient);
				mRepository.insert(proxy);
			} catch (IOException e) {
				if (mServerThread.isInterrupted()) {
					return;
				}
				e.printStackTrace();
			}			
		}
	}
	

	
}
