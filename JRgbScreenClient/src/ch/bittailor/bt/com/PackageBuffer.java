package ch.bittailor.bt.com;


public class PackageBuffer implements IPackageBuffer {

	byte mData[];
	int mPutPosition;
	int mGetPosition;
	
	public PackageBuffer(int iSize) {
		mData = new byte[iSize];
		mPutPosition = 0;
		mGetPosition = 0;
	}
	
	@Override
	public int put(byte iValue) {
		if (mPutPosition < mData.length) {
			mData[mPutPosition] = iValue;
			mPutPosition++;
			return 1;
		}
		return 0;
	}

	@Override
	public int get() {
		if (mGetPosition < mData.length) {
			return mData[mGetPosition++];
		}
		return -1;
	}

	@Override
	public int length() {
		return mPutPosition - mGetPosition;
	}

	@Override
	public void clear() {
		mPutPosition = 0;
        mGetPosition = 0;
	}

	@Override
	public byte[] raw() {
		return mData;
	}

	@Override
	public void filled(int iLength) {
		mPutPosition = iLength;
        mGetPosition = 0;		
	}

}
