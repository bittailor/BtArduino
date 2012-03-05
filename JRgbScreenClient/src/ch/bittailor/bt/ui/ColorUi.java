package ch.bittailor.bt.ui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingUtilities;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ch.bittailor.bt.com.ConnectionFactory;
import ch.bittailor.bt.com.TcpRequestClient;

public class ColorUi extends JFrame implements ChangeListener {

	private static final long serialVersionUID = 1L;
	private JSpinner segment;
	
	private JSpinner rc;
	private JSpinner gc;
	private JSpinner bc;
	private JColorChooser c;

	private IRgbScreen mScreen;
	private JButton persistButton;
	
	public ColorUi(IRgbScreen screen) throws HeadlessException {
		super("Color");
		
		this.mScreen = screen;
		
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
				Color color = c.getColor();
				System.out.println("color = " + color.toString());
				mScreen.fill(color);
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
		final ConnectionFactory connectionFactory = new ConnectionFactory("192.168.2.2",2000);							
		TcpRequestClient requestClient = new TcpRequestClient(connectionFactory);
		final RgbScreenProxy screen = new RgbScreenProxy(requestClient);		
		
		SwingUtilities.invokeLater(new Runnable() {
		    public void run() {
		        new ColorUi(screen);
		    }
		});
    }
	
	
	
	
}
