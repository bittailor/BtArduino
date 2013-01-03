package ch.bittailor.bt.ci.server;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import ch.bittailor.bt.ci.CiLedMatrix;
import ch.bittailor.bt.ci.ILogFilesCollector;
import ch.bittailor.bt.ci.IProject;
import ch.bittailor.bt.ci.LogFilesCollector;
import ch.bittailor.bt.ci.Project;
import ch.bittailor.bt.ui.RgbScreenRepository;
import ch.bittailor.bt.ui.RgbScreenServer;

public class ServerMain {

	public static void main(String[] args) {
		
		ILogFilesCollector logFilesCollector = new LogFilesCollector();
		
		List<IProject> projects = new ArrayList<IProject>();
		for (String logFileDirectory : args) {
			projects.add(new Project(logFileDirectory, logFilesCollector));
		}
			
		ScheduledExecutorService executorService = Executors.newScheduledThreadPool(2); 
		RgbScreenRepository repository = new RgbScreenRepository(16, 16, executorService);
		final CiLedMatrix ciLedMatrix = new CiLedMatrix(repository.getMasterScreen(), projects);
		RgbScreenServer server;
		try {
			server = new RgbScreenServer(8645, repository);	
			server.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		executorService.scheduleAtFixedRate(new Runnable() {
			
			@Override
			public void run() {
				try {
					ciLedMatrix.update();
				} catch (Throwable throwable) {
					throwable.printStackTrace();
				}
			}
		}, 0, 10, TimeUnit.SECONDS);
	}
}
