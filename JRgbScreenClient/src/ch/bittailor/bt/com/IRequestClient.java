package ch.bittailor.bt.com;

public interface IRequestClient {

	IOutputPackage out();
    IInputPackage in();

    /**
     * Sends an action request. 
     * An action request is a request without return value. 
     */
    void sendActionRequest();
    
    /**
     * Sends a function request. 
     * An query request is a request with return value. 
     */
    void sendQueryRequest();
	
}
