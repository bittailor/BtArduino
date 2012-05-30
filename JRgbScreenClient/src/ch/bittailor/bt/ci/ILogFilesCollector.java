package ch.bittailor.bt.ci;

public interface ILogFilesCollector {

	Iterable<String> collect(String iLogFolder);

}
