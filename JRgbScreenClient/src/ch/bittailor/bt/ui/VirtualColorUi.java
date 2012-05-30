package ch.bittailor.bt.ui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingUtilities;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class VirtualColorUi extends JFrame implements ChangeListener {

	private static final long serialVersionUID = 1L;
	private JSpinner segment;
	
	private JSpinner rc;
	private JSpinner gc;
	private JSpinner bc;
	private JColorChooser c;

	private IRgbScreen mScreen;
	private IRgbScreenPanel mScreenPanel;
	private JButton persistButton;
	
	public VirtualColorUi(IRgbScreenPanel screenPanel, IRgbScreen screen) {
		super("Color");
		
		this.mScreen = screen;
		this.mScreenPanel = screenPanel;
		
		Color whiteBalance = mScreen.whiteBalance(0);
		
		JPanel root = new JPanel(new BorderLayout());
		JPanel top = new JPanel(new GridLayout(4, 1));
		root.add(top,BorderLayout.NORTH);
	  
		segment = new JSpinner(new SpinnerNumberModel(0,0,3,1));
		segment.addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent iE) {
				Color newWhiteBalance = mScreen.whiteBalance(getIntegerValue(segment));
				rc.setValue(new Integer(newWhiteBalance.getRed()));
				gc.setValue(new Integer(newWhiteBalance.getGreen()));
				bc.setValue(new Integer(newWhiteBalance.getBlue()));
				
			}
		});
		
		rc = new JSpinner(new SpinnerNumberModel(whiteBalance.getRed(),0,63,1));
		gc = new JSpinner(new SpinnerNumberModel(whiteBalance.getGreen(),0,63,1));
		bc = new JSpinner(new SpinnerNumberModel(whiteBalance.getBlue(),0,63,1));
		
		rc.addChangeListener(this);
		gc.addChangeListener(this);
		bc.addChangeListener(this);
		
		top.add(segment);
		
		top.add(rc);
		top.add(gc);
		top.add(bc);
		top.add(bc);
		
		
		persistButton = new JButton("Persist White Balance");
		
		persistButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent iE) {
				mScreen.persistWhiteBalance(getIntegerValue(segment));
			}
		});
		
		top.add(persistButton);
		
		c = new JColorChooser(Color.BLUE);
		root.add(c);
		c.getSelectionModel().addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
			}
		});
		
		
		JButton fillButton = new JButton("Fill"); 
		fillButton.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent iE) {
				Color color = c.getColor();
				System.out.println("color = " + color.toString());
				mScreen.fill(color);
				mScreen.repaint();
				
			}
		});
		root.add(fillButton,BorderLayout.SOUTH);
		
		mScreenPanel.addListener(new MouseAdapter() {

			@Override
			public void mousePressed(MouseEvent iE) {
				mScreen.setPixel(iE.getX(), iE.getY(), c.getColor());
				mScreen.repaint();
			}
			
		});

		getContentPane().add(root);
		
//		serial = new Serial("/dev/tty.usbmodem621");
		
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		pack();
		setVisible(true);
	}
	
	private int getIntegerValue(JSpinner spinner) {
		return ((SpinnerNumberModel)spinner.getModel()).getNumber().intValue();
	}
	
	
	@Override
	public void stateChanged(ChangeEvent e) {
		Color whiteBalance = new Color(getIntegerValue(rc),getIntegerValue(gc),getIntegerValue(bc));
		System.out.println("whiteBalance = " + whiteBalance.toString());
		mScreen.setWhiteBalance(whiteBalance, getIntegerValue(segment));
		System.out.println("read whiteBalance = " + mScreen.whiteBalance(getIntegerValue(segment)));
	}
	
	public static void main ( String[] args )
    {
			
		
		SwingUtilities.invokeLater(new Runnable() {
		    public void run() {
		        
		    	RgbScreenMultiplexer screen = new RgbScreenMultiplexer(16,16);
		    	
//		    	ConnectionFactory connectionFactory = new ConnectionFactory("192.168.2.2",2000);	
//				TcpRequestClient requestClient = new TcpRequestClient(connectionFactory);
//				RgbScreenProxy remoteScreen = new RgbScreenProxy(requestClient);	
//				screen.add(remoteScreen);

				VirtualRgbScreen virtualScreen = new VirtualRgbScreen(16,16);
		    	screen.add(virtualScreen);
		        
		        
		        JFrame frame = new JFrame();
		    	frame.getContentPane().add(virtualScreen);
		    	frame.pack();
		    	frame.setVisible(true);
		        
		    	
		    	new VirtualColorUi(virtualScreen,screen);
		    }
		});
    }
	
	
	
	
}
