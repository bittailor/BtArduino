package ch.bittailor.bt.ui;

import java.awt.Color;
import java.awt.FontFormatException;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;

import ch.bittailor.bt.com.ConnectionFactory;
import ch.bittailor.bt.com.TcpRequestClient;

public class ImageScreenTestTwo {


	private static void draw(IRgbScreen screen, final ImageScreen iImageScreen) throws FontFormatException, IOException {

		BufferedImage image = new BufferedImage(8, 8, BufferedImage.TYPE_INT_RGB);
		Graphics2D graphics = (Graphics2D)image.getGraphics();
//		graphics.setBackground(Color.RED);
//		graphics.clearRect(0, 0, 7, 7);
		graphics.setColor(Color.BLUE);		
		graphics.drawOval(0, 0, 6, 6);
		graphics.drawLine(3, 3, 3, 0);
		
		
		
		iImageScreen.getGraphics().drawImage(image, 4, 0, null);
		iImageScreen.repaint();
		sleep();
		iImageScreen.getGraphics().clearRect(0, 0, iImageScreen.getImage().getWidth(null), iImageScreen.getImage().getHeight((null)));
		//graphics.setTransform();
		AffineTransform affineTransform = new AffineTransform();
		affineTransform.translate(11, 0);
		affineTransform.rotate(Math.toRadians(90));
		//affineTransform.translate(0, 0);
		
		//AffineTransform affineTransform = AffineTransform.getRotateInstance(Math.toRadians(90),-3,-3);
		iImageScreen.getGraphics().drawImage(image, affineTransform , null);
		iImageScreen.repaint();
		
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				JFrame frame = new JFrame("Image");
				JLabel label = new JLabel(new ImageIcon(iImageScreen.getImage()),SwingConstants.CENTER);
				frame.getContentPane().add(label);
				frame.pack();
				frame.setVisible(true);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			}
		});
		
		
		/*
		Font tinyFont = Font.createFont(Font.TRUETYPE_FONT,ImageScreenTest.class.getResourceAsStream("tiny.ttf"));
		
		Font oldFont = graphics.getFont();
		graphics.setFont(tinyFont.deriveFont(6f));
		graphics.drawString("Hello", 0, 7);
		iImageScreen.repaint();*/
		
		/*
		graphics.setColor(Color.BLUE);
		graphics.drawLine(0, 2, 15, 2);
		graphics.drawLine(0, 5, 15, 5);

		
		graphics.setColor(Color.GREEN);
		graphics.fill3DRect(0, 0, 4, 2, false);
		graphics.fill3DRect(6, 0, 4, 2, false);
		graphics.fill3DRect(6, 0, 4, 2, false);
		iImageScreen.repaint();
		*/
		
		/*
		graphics.setColor(Color.RED);
		graphics.draw(new Ellipse2D.Double(0,0,15,7));
		iImageScreen.repaint();
		
		graphics.setColor(Color.YELLOW);
		graphics.draw(new Ellipse2D.Double(4,0,7,7));
		iImageScreen.repaint();
		
		graphics.setColor(Color.BLUE);
		graphics.draw(new Line2D.Double(0, 0, 15, 7));
		iImageScreen.repaint();
		*/
		/*
		SwingUtilities.invokeLater(new Runnable() {
			
			@Override
			public void run() {
				JFrame frame = new JFrame("Image");
				JLabel label = new JLabel(new ImageIcon(iImageScreen.getImage()),SwingConstants.CENTER);
				frame.getContentPane().add(label);
				frame.pack();
				frame.setVisible(true);
				frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			}
		});
		*/
		
				
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

		for (int i = 0; i < 1 ; i++) {
			System.out.println("Loop " + i);		
			try {
				final ConnectionFactory connectionFactory = new ConnectionFactory("192.168.2.2",2000);							
				TcpRequestClient requestClient = new TcpRequestClient(connectionFactory);
				RgbScreenProxy screen = new RgbScreenProxy(requestClient);	
				screen.fill(Color.black);
				screen.repaint();
				ImageScreen imageScreen = new ImageScreen(screen);
				draw(screen,imageScreen);
				requestClient.close();
				System.out.print("Sleep ...");
				Thread.sleep(1000);
				System.out.println("... done");
			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (FontFormatException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	
}
