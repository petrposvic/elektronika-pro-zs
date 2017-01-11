package cz.posvic.ovladac;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
	private static final String TAG = MainActivity.class.getName();
	private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

	// MAC adresa bluetooth modulu
	// private static final String ADDRESS = "00:00:12:09:18:48";
	// private static final String ADDRESS = "20:15:04:29:07:65";

	private final int RECEIVE_MESSAGE = 1;

	private BluetoothAdapter mBluetoothAdapter;
	private BluetoothSocket mBluetoothSocket;
	private ConnectedThread mConnectedThread;

	private StringBuilder sb = new StringBuilder();
	private Handler mReceiveHandler;

	private TextView state, message;

	// Vola se pri spusteni aplikace, pouze jednou
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Nastavi rozvrzeni
		setContentView(R.layout.activity_main);

		// Najde textove pole v rozvrzeni
		state = (TextView) findViewById(R.id.state);

		// Najde textove pole v rozvrzeni
		message = (TextView) findViewById(R.id.message);

		// Najde tlacitko 1 v rozvrzeni
		Button button1 = (Button) findViewById(R.id.button1);

		// Kliknuti na tlacitko 1 odesle text do bluetooth modulu
		button1.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				bluetoothSend("d");
			}
		});

		// Najde tlacitko 2 v rozvrzeni
		Button button2 = (Button) findViewById(R.id.button2);

		// Kliknuti na tlacitko 2 odesle text do bluetooth modulu
		button2.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				bluetoothSend("c");
			}
		});

		// Zde se prijimaji zpravy z bluetooth modulu
		mReceiveHandler = new Handler() {
			public void handleMessage(android.os.Message msg) {
				switch (msg.what) {
					case RECEIVE_MESSAGE:
						byte[] buffer = (byte[]) msg.obj;
						sb.append(new String(buffer, 0, msg.arg1));

						int endOfLineIndex = sb.indexOf("\r\n");
						if (endOfLineIndex > 0) {
							final String text = sb.substring(0, endOfLineIndex);
							Log.d(TAG, "received = " + text);
							message.setText(text);

							if ("pokus".equals(text)) {
								// Bluetooth modul odeslal "pokus"
							}
							sb.delete(0, sb.length());
						}

						break;
				}
			}
		};

		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
	}

	// Vola se pri kazdem vstupu do aplikace
	@Override
	protected void onResume() {
		super.onResume();

		// Vytvoreni spojeni s bluetooth modulem
		try {
			mBluetoothSocket = createBluetoothSocket(mBluetoothAdapter.getRemoteDevice(ADDRESS));
		} catch (IOException e) {
			Log.e(TAG, e.toString());
		}

		// Discovery is resource intensive. Make sure it isn't going on
		// when you attempt to connect and pass your message.
		mBluetoothAdapter.cancelDiscovery();

		new BluetoothConnect().execute();
	}

	// Vola se pri pozastaveni aplikace
	@Override
	protected void onPause() {
		super.onPause();
		Log.d(TAG, "-- onPause() --");

		// Uzavreni spojeni s bluetooth modulem
		try {
			state.setText("Odpojeno");
			mBluetoothSocket.close();
		} catch (IOException e) {
			Log.e(TAG, e.toString());
		}
	}

	private class BluetoothConnect extends AsyncTask<Void, Void, Boolean> {

		@Override
		protected void onPreExecute() {
			state.setText("Pripojovani");
		}

		@Override
		protected Boolean doInBackground(Void... params) {

			// Establish the connection. This will block until it connects.
			try {
				mBluetoothSocket.connect();
				return Boolean.TRUE;
			} catch (IOException e1) {
				Log.e(TAG, e1.toString());
				try {
					mBluetoothSocket.close();
				} catch (IOException e2) {
					Log.e(TAG, e2.toString());
				}
			}

			return Boolean.FALSE;
		}

		@Override
		protected void onPostExecute(Boolean success) {

			// Pokud se uspesne pripojil bluetooth modul (succes), zmen text na Pripojeno, jinak
			// na Odpojeno
			if (success) {
				state.setText("Připojeno");

				mConnectedThread = new ConnectedThread(mBluetoothSocket);
				mConnectedThread.start();
			} else {
				state.setText("Odpojeno");
			}
		}
	}

	// ------------------------------------------------------------------------
	// Bluetooth
	// ------------------------------------------------------------------------

	// Odesila text do bluetooth modulu
	private void bluetoothSend(String str) {
		Log.d(TAG, "-- bluetoothSend(" + str + ") --");

		if (mConnectedThread == null) {
			Log.e(TAG, "no bluetooth connection");
			return;
		}

		mConnectedThread.write(str);
	}

	private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
		if (Build.VERSION.SDK_INT >= 10){
			try {
				final Method m = device
						.getClass()
						.getMethod(
								"createInsecureRfcommSocketToServiceRecord",
								new Class[] { UUID.class }
						);
				return (BluetoothSocket) m.invoke(device, MY_UUID);
			} catch (Exception e) {
				Log.e(TAG, "Could not create Insecure RFComm Connection", e);
			}
		}

		return  device.createRfcommSocketToServiceRecord(MY_UUID);
	}

	private class ConnectedThread extends Thread {
		private final InputStream mmInStream;
		private final OutputStream mmOutStream;

		ConnectedThread(BluetoothSocket socket) {
			InputStream tmpIn = null;
			OutputStream tmpOut = null;

			// Get the input and output streams, using temp objects because
			// member streams are final
			try {
				tmpIn = socket.getInputStream();
				tmpOut = socket.getOutputStream();
			} catch (IOException e) {
				// Ignore
			}

			mmInStream = tmpIn;
			mmOutStream = tmpOut;
		}

		public void run() {
			byte[] buffer = new byte[256];
			int bytes;

			while (true) {
				try {
					bytes = mmInStream.read(buffer);
					mReceiveHandler.obtainMessage(
							RECEIVE_MESSAGE,
							bytes, -1, buffer
					).sendToTarget();
				} catch (IOException e) {
					break;
				}
			}
		}

		void write(String message) {
			Log.d(TAG, "...Data to send: " + message + "...");
			byte[] msgBuffer = message.getBytes();
			try {
				mmOutStream.write(msgBuffer);
			} catch (IOException e) {
				Log.d(TAG, "...Error data send: " + e.getMessage() + "...");
			}
		}
	}
}
