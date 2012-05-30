package ch.bittailor.bt.ci;

import static org.easymock.EasyMock.createControl;
import static org.easymock.EasyMock.expect;
import static org.junit.Assert.*;

import java.awt.Image;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import org.easymock.IMocksControl;
import org.junit.Test;

import ch.bittailor.bt.ui.ImageScreen;
import ch.bittailor.bt.ui.VirtualRgbScreen;

public class CiLedMatrixTest {

	public void test() {
		final VirtualRgbScreen screen = new VirtualRgbScreen(16, 16);
		
		SwingUtilities.invokeLater(new Runnable() {			
			@Override
			public void run() {
				JFrame frame = new JFrame();
				frame.getContentPane().add(screen);
				frame.pack();
				frame.setVisible(true);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			}
		});
		
		

		IMocksControl control = createControl();
		ILogFilesCollector logFilesCollector1 = control.createMock(ILogFilesCollector.class);
		ILogFilesCollector logFilesCollector2 = control.createMock(ILogFilesCollector.class);
		
		List<String> log1 = new ArrayList<String>();
		log1.add("log20120419085114.xml");
		log1.add("log20120419085113.xml");
		log1.add("log20120419085112.xml");
		log1.add("log20120419085111Lbuild.xml");
		log1.add("log20120419085110Lbuild.xml");
		log1.add("log20120419085109.xml");
		log1.add("log20120419085108Lbuild.xml");
		log1.add("log20120419085107.xml");
		log1.add("log20120419085106Lbuild.xml");
		log1.add("log20120419085105Lbuild.xml");
		log1.add("log20120419085104Lbuild.xml");
		log1.add("log20120419085103.xml");
		log1.add("log20120419085102Lbuild.xml");
		log1.add("log20120419085101Lbuild.xml");
		log1.add("log20120419085100Lbuild.xml");
		
		
		
		List<String> log2 = new ArrayList<String>();
		log2.add("log20120419085114Lbuild.xml");
		log2.add("log20120419085113.xml");
		log2.add("log20120419085112.xml");
		log2.add("log20120419085111Lbuild.xml");
		log2.add("log20120419085110Lbuild.xml");
		log2.add("log20120419085109Lbuild.xml");
		log2.add("log20120419085108Lbuild.xml");
		log2.add("log20120419085107.xml");
		log2.add("log20120419085106Lbuild.xml");
		log2.add("log20120419085105.xml");
		log2.add("log20120419085104Lbuild.xml");
		log2.add("log20120419085103.xml");
		log2.add("log20120419085102Lbuild.xml");
		log2.add("log20120419085101.xml");
		log2.add("log20120419085100Lbuild.xml");
		
		List<String> current1 = new ArrayList<String>();
		List<String> current2 = new ArrayList<String>();
		
		
		
	
		expect(logFilesCollector1.collect("p1")).andReturn(current1).anyTimes() ;
		expect(logFilesCollector2.collect("p2")).andReturn(current2).anyTimes() ;
		
		control.replay();
		
		List<IProject> projects = new ArrayList<IProject>();
		projects.add(new Project("p1", logFilesCollector1));
		projects.add(new Project("p2", logFilesCollector2));
		
		
		//ImageScreen image = new ImageScreen(screen);
		//ProjectLedMatrix projectLedMatrix = new ProjectLedMatrix(projects.get(0), image.getImage() );
		
		//projectLedMatrix.update();
		//image.repaint();
		
		CiLedMatrix matrix = new CiLedMatrix(screen, projects);
		matrix.update();
		
		
		while( !log1.isEmpty() || log2.isEmpty() ) {
			if (!log1.isEmpty()) {
				current1.add(log1.remove(log1.size()-1));
			}
			if (!log2.isEmpty()) {
				current2.add(log2.remove(log2.size()-1));
			}
			matrix.update();
			sleep();	
		}
		control.verify();
		
	}

	private void sleep() {
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new CiLedMatrixTest().test();
	}
	
}
