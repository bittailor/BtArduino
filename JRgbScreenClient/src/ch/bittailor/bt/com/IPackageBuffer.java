package ch.bittailor.bt.com;

public interface IPackageBuffer {
	 
	 int put(byte iValue);
     int get();
     int length();

     void clear();
     byte[] raw();
     void filled(int iLength);
     
}
