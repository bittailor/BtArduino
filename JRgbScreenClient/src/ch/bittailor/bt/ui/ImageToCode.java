package ch.bittailor.bt.ui;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;

import javax.imageio.ImageIO;

public class ImageToCode {

	
	public static void main(String[] args) throws URISyntaxException, IOException {
		File iconFolder = new File(ImageScreenTest.class.getResource("icons").toURI());
		String file = "angel_sm.png";
		BufferedImage icon = ImageIO.read(new File(iconFolder,file));
		
		for (int x = 0; x < icon.getWidth(); x++) {
			System.out.print("{");
			for (int y = 0; y < icon.getHeight(); y++) {
//				Color pixel = new Color(icon.getRGB(x, y));
//				System.out.print("Color("+pixel.getRed() + "," + pixel.getGreen() + "," + pixel.getBlue()+")");
				System.out.print(icon.getRGB(x, y));
				if (y < icon.getHeight()-1) {
					System.out.print(",");
				}
			}
			System.out.println("},");
		}
		
	}
	
}
