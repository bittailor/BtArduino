package ch.bittailor.bt.ui;

import java.util.concurrent.ExecutorService;

public class RgbScreenRepository implements IRgbScreenRepository {

	private ExecutorService mExecutorService;
	private RgbScreenMultiplexer mMultiplexer;
	
	public RgbScreenRepository(int iWidth, int iHeight, ExecutorService iExecutorService) {
		mExecutorService = iExecutorService;
		mMultiplexer = new RgbScreenMultiplexer(iWidth,iHeight);
	}

	public IRgbScreen getMasterScreen() {
		return mMultiplexer;
	}
	
	@Override
	public void insert(final IRgbScreen iScreen) {
		mExecutorService.submit(new Runnable() {
			
			@Override
			public void run() {
				// TODO fix constant project name
				insertScreen(iScreen);
			}
		});
	}
	
	private synchronized void insertScreen(IRgbScreen iScreen ) {
		mMultiplexer.add(iScreen);
	}

}
