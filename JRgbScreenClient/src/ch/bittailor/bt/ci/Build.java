package ch.bittailor.bt.ci;


public class Build implements IBuild {
	
	// GOOD build : log20120419085114Lbuild.136.xml
	// FAILED build : log20120405135316.xml
	
	private final long mId;
	private final Status mStatus;
	
	public Build(String iLogFile) {
		mStatus = status(iLogFile);
		mId = id(iLogFile);
	}

	@Override
	public Status getStatus() {
		return mStatus;
	}
	
	@Override
	public long getId() {
		return mId;
	}
	
	
	@Override
	public int compareTo(IBuild iOther) {
		if (mId < iOther.getId()) {
			return 1;
		}
		if (mId == iOther.getId()) {
			return 0;
		}
		return -1;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + (int) (mId ^ (mId >>> 32));
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Build other = (Build) obj;
		if (mId != other.mId)
			return false;
		return true;
	}

	private long id(String iFileName) {
		String idString = iFileName.substring(3, 17);
		try {
			return Long.parseLong(idString);
		} catch (NumberFormatException e) {
			return 0;
		}
	}

	private Status status(String iFileName) {
		if (iFileName.contains("Lbuild")) {
			return Status.GOOD;
		}
		return Status.FAILED;
	}

	

}
