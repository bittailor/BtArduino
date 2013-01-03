package ch.bittailor.bt.ui;

import java.awt.Color;
import java.awt.FontFormatException;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.net.URISyntaxException;
import java.net.UnknownHostException;

import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;


public class ImageScreenTest {


	private static void draw(final ImageScreen iImageScreen) throws FontFormatException, IOException {
		try {
			File iconFolder = new File(ImageScreenTest.class.getResource("icons").toURI());
			for ( String file : iconFolder.list()) {
				if (!file.endsWith(".png")) {
					continue;
				}
				System.out.println("draw " + file);
				iImageScreen.getScreen().fill(Color.black);
				iImageScreen.repaint();
				final BufferedImage icon = ImageIO.read(new File(iconFolder,file));
				iImageScreen.getGraphics().drawImage(icon, 0, 0, null);
				iImageScreen.repaint();
				
				SwingUtilities.invokeAndWait(new Runnable() {
					
					@Override
					public void run() {
						JFrame frame = new JFrame("Image");
						
						frame.getContentPane().setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
						frame.getContentPane().add(new JLabel(new ImageIcon(iImageScreen.getImage()),SwingConstants.CENTER));
						frame.getContentPane().add(new JLabel(new ImageIcon(icon),SwingConstants.CENTER));
						frame.pack();
						frame.setVisible(true);
						frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
					}
				});
				
				
			}
		} catch (URISyntaxException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
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
	
	/*
	
	private static void sleep() {
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	*/

	public static void main(String[] args) {

		for (int i = 0; i < 1 ; i++) {
			System.out.println("Loop " + i);		
			try {
				
				VirtualRgbScreen virtualScreen = new VirtualRgbScreen(16,16);
				
				//final ConnectionFactory connectionFactory = new ConnectionFactory("192.168.2.2",2000);							
				//TcpRequestClient requestClient = new TcpRequestClient(connectionFactory);
				//RgbScreenProxy screen = new RgbScreenProxy(requestClient);		
				ImageScreen imageScreen = new ImageScreen(virtualScreen);
				draw(imageScreen);
				
				 JFrame frame = new JFrame();
			    	frame.getContentPane().add(virtualScreen);
			    	frame.pack();
			    	frame.setVisible(true);
				
				//requestClient.close();
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
