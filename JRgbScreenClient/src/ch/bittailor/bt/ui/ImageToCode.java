package ch.bittailor.bt.ui;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;

import javax.imageio.ImageIO;

public class ImageToCode {

	
	public static void main(String[] args) throws URISyntaxException, IOException {
		File iconFolder = new File(ImageScreenTest.class.getResource("icons").toURI());
		for (int i = 1; i < 7; i++) {
			String file = "BtTrain" + i + ".png";
			BufferedImage icon = ImageIO.read(new File(iconFolder,file));
			System.out.println("");
			System.out.println("//*************************************************************************************************");
			System.out.println("");
			System.out.println("extern const uint32_t BT_TRAIN_"+i+"[Image::SIZE][Image::SIZE] PROGMEM;");
			System.out.println("const uint32_t BT_TRAIN_"+i+"[Image::SIZE][Image::SIZE] =");
			System.out.println("{");
			for (int x = 0; x < icon.getWidth(); x++) {
				System.out.print("{");
				for (int y = 0; y < icon.getHeight(); y++) {
					System.out.print(icon.getRGB(x, y));
					if (y < icon.getHeight()-1) {
						System.out.print(",");
					}
				}
				System.out.println("},");
			}
			System.out.println("};");
		}
		
		
		
		
		
		
		
		
	}
	
}
