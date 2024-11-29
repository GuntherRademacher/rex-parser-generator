package de.bottlecaps.rex.test.base;

import java.io.IOException;
import java.io.InputStream;

public class StreamCollector extends Thread
{
  InputStream stream;
  String string;

  public StreamCollector(InputStream s)
  {
    stream = s;
    string = null;
    start();
  }

  @Override
  public String toString()
  {
    if (string == null)
    {
      try
      {
        join();
      }
      catch (InterruptedException e)
      {
        throw new RuntimeException(e);
      }
    }
    return string;
  }

  @Override
  public void run()
  {
    try
    {
      byte buffer[] = new byte[2 * 1024 * 1024];
      int size = 0;
      for (int n = 0; n >= 0; n = stream.read(buffer, size, buffer.length - size))
      {
        size += n;
        if (size == buffer.length)
        {
          for (; stream.read() >= 0; ) {}
          break;
        }
      }
      stream.close();
      string = new String(buffer, 0, size, "UTF-8");
    }
    catch (IOException e)
    {
      throw new RuntimeException(e);
    }
  }
}
