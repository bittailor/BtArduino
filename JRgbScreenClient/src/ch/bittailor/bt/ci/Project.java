package ch.bittailor.bt.ci;

import java.util.Collection;
import java.util.SortedSet;
import java.util.TreeSet;

public class Project implements IProject {

	private String mLogFolder;
	private SortedSet<IBuild>  mBuilds;
	private ILogFilesCollector mLogFilesCollector;
	
	public Project(String iLogFolder, ILogFilesCollector iLogFilesCollector) {
		mLogFolder = iLogFolder;
		mLogFilesCollector = iLogFilesCollector;
		update();
	}
	

	@Override
	public Collection<IBuild> getHistrory() {
		return mBuilds;
	}
	
	
	public void update() {
		readLogs();
	}

	private void readLogs() {
		mBuilds = new TreeSet<IBuild>();		
		Iterable<String> logs = mLogFilesCollector.collect(mLogFolder);
		for (String file : logs) {			
			anaylse(file);
		}
	}

	private void anaylse(String iFile) {
		mBuilds.add(new Build(iFile));		
	}
}
