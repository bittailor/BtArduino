package ch.bittailor.bt.com;

public interface IRequestClient {

	public IOutputPackage out();
	public IInputPackage in();

    /**
     * Sends an action request. 
     * An action request is a request without return value. 
     */
	public void sendActionRequest();
    
    /**
     * Sends a function request. 
     * An query request is a request with return value. 
     */
	public void sendQueryRequest();
    
	public void close();
	
	public boolean isDisposed();
	
}
