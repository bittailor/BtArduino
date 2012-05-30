package ch.bittailor.bt.ui;

import java.awt.Color;

import ch.bittailor.bt.com.IInputPackage;
import ch.bittailor.bt.com.IOutputPackage;
import ch.bittailor.bt.com.IRequestServer;
import ch.bittailor.bt.ui.RgbScreenProxy.Cmd;

public class RgbScreenRequestServer implements IRequestServer {

	private IRgbScreen mScreen;
	
	public RgbScreenRequestServer(IRgbScreen iScreen) {
		mScreen = iScreen;
	}

	@Override
	public void handleRequest(IInputPackage iInputPackage, IOutputPackage iOutputPackage) {
		
		Cmd command = RgbScreenProxy.Cmd.values()[iInputPackage.readUInt8()];
		
		switch (command) {
		case WIDTH : {
			iOutputPackage.writeUInt8(mScreen.width());
		} break;
		case HEIGHT : {
			iOutputPackage.writeUInt8(mScreen.height());
		} break;
		case SET_PIXEL : {	
			setPixel(iInputPackage,iOutputPackage);
		} break;
		case FILL : {
			fill(iInputPackage,iOutputPackage);
		} break;
		case REPAINT : {
			repaint(iInputPackage,iOutputPackage);
		} break;
		case NUMBER_OF_SEGMENTS : {
			iOutputPackage.writeUInt8(mScreen.numberOfSegments());
		} break;
		case WHITE_BALANCE : {
			Color whiteBalance = mScreen.whiteBalance(iInputPackage.readUInt8());
			addColor(iOutputPackage, whiteBalance); 
		} break;
		case SET_WHITE_BALANCE : {
			setWhiteBalance(iInputPackage,iOutputPackage);
		} break;
		case PERSIST_WHITE_BALANCE : {
			mScreen.persistWhiteBalance(iInputPackage.readUInt8());
		} break;
		default : {
		} break;
		}

	}
	
	private void setWhiteBalance(IInputPackage iInputPackage, IOutputPackage iOutputPackage) {
		Color color = new Color(iInputPackage.readUInt8(),iInputPackage.readUInt8(),iInputPackage.readUInt8());
		int segment = iInputPackage.readUInt8();
		mScreen.setWhiteBalance(color, segment);
	}

	private void repaint(IInputPackage iInputPackage, IOutputPackage iOutputPackage) {
		mScreen.repaint();		
	}

	private void fill(IInputPackage iInputPackage, IOutputPackage iOutputPackage) {
		Color color = new Color(iInputPackage.readUInt8(),iInputPackage.readUInt8(),iInputPackage.readUInt8());
		mScreen.fill(color);
	}

	private void setPixel(IInputPackage iInputPackage, IOutputPackage iOutputPackage) {
		int x = iInputPackage.readUInt8();
		int y = iInputPackage.readUInt8();
		Color color = new Color(iInputPackage.readUInt8(),iInputPackage.readUInt8(),iInputPackage.readUInt8());
		mScreen.setPixel(x,y,color);
		
	}

	private void addColor(IOutputPackage ioOut, Color iColor) {
		ioOut.writeUInt8(iColor.getRed());
		ioOut.writeUInt8(iColor.getGreen());
		ioOut.writeUInt8(iColor.getBlue());
	}

}
