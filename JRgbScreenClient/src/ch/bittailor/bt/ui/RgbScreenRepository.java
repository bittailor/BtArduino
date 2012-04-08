package ch.bittailor.bt.ui;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;

public class RgbScreenRepository implements IRgbScreenRepository {

	private ExecutorService mExecutorService;
	private Map<String, List<IRgbScreen>> mScreens = new HashMap<String, List<IRgbScreen>>();
	
	
	@Override
	public void insert(final IRgbScreen iScreen) {
		mExecutorService.submit(new Runnable() {
			
			@Override
			public void run() {
				// TODO fix constant project name
				insertScreen("trunk",iScreen);
			}
		});
	}
	
	private synchronized void insertScreen(String iProject, IRgbScreen iScreen ) {
		if (!mScreens.containsKey(iProject)) {
			mScreens.put(iProject, new ArrayList<IRgbScreen>());
		}
		mScreens.get(iProject).add(iScreen);
	}

}
