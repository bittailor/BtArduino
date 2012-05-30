package ch.bittailor.bt.ci;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class LogFilesCollector implements ILogFilesCollector {

	
	@Override
	public Iterable<String> collect(String iLogFolder) {
		File folder = new File(iLogFolder);
		List<String> logFiles = new ArrayList<String>();
				
		if (!folder.isDirectory()) {
			return logFiles;
		}
		
		for (String file : folder.list()) {			
			if (file.endsWith(".xml")) {
				logFiles.add(file);
			}
		}
		
		return logFiles;
	}

}
