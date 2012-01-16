package ch.bittailor.bt.com;

public interface IRequestClient {

	IOutputPackage out();
    IInputPackage in();

    void sendRequest();
	
}
