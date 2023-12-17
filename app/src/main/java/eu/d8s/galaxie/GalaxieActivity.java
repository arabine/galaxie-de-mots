 
package eu.d8s.galaxie;

import org.libsdl.app.SDLActivity;

import com.hoho.android.usbserial.driver.SerialTimeoutException;
import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;
import com.hoho.android.usbserial.driver.UsbSerialProber;

import java.io.File;
import java.io.IOException;
import java.util.ArrayDeque;
import java.util.EnumSet;

import android.os.Bundle;
import android.util.Log;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
/* 
 * A sample wrapper class that just calls SDLActivity 
 */ 

public class GalaxieActivity extends SDLActivity implements SerialListener
{
    private final static String TAG = "GalaxieActivity";
    DatabaseHelper dbHelper = null;

    private enum Connected { False, Pending, True }

    // private final BroadcastReceiver broadcastReceiver;
    private int deviceId, portNum, baudRate;
    private UsbSerialPort usbSerialPort;
    private SerialService service;
    private Connected connected = Connected.False;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

// /data/data/com.me.myapp/databases/
        String db = "/data/data/" + getContext().getPackageName() + "/databases";

        File dbDir = new File(db);
        if (!dbDir.exists())
        {
            Log.e(TAG, "Created path: " + db);
            dbDir.mkdirs();
        }

        dbHelper = new DatabaseHelper(this, db);
        try {
            dbHelper.prepareDatabase();
        } catch (IOException e) {
            Log.e(TAG, e.getMessage());
        }
    }

    private void disconnect() {
        connected = Connected.False;
        service.disconnect();
        usbSerialPort = null;
    }

    @Override
    public void onDestroy() {
        if (connected != Connected.False)
            disconnect();
        stopService(new Intent(this, SerialService.class));
        super.onDestroy();
    }

    @Override
    public void onStart() {
        super.onStart();
        if(service != null)
            service.attach(this);
        else
            startService(new Intent(this, SerialService.class)); // prevents service destroy on unbind from recreated activity caused by orientation change
    }

    @Override
    public void onStop() {
        if(service != null && !isChangingConfigurations())
            service.detach();
        super.onStop();
    }


     private native void printFromJava(String txt);

    void status(String str) {
        printFromJava(str);
    }

    /*
     * SerialListener
     */
    @Override
    public void onSerialConnect() {
        status("connected");
        connected = Connected.True;
    }

    @Override
    public void onSerialConnectError(Exception e) {
        status("connection failed: " + e.getMessage());
        disconnect();
    }

    @Override
    public void onSerialRead(byte[] data) {
        ArrayDeque<byte[]> datas = new ArrayDeque<>();
        datas.add(data);
        // receive(datas);
    }

    public void onSerialRead(ArrayDeque<byte[]> datas) {
        // receive(datas);
    }

    @Override
    public void onSerialIoError(Exception e) {
        status("connection lost: " + e.getMessage());
        disconnect();
    }


 /**
     * This method is called by SDL before loading the native shared libraries.
     * It can be overridden to provide names of shared libraries to be loaded.
     * The default implementation returns the defaults. It never returns null.
     * An array returned by a new implementation must at least contain "SDL2".
     * Also keep in mind that the order the libraries are loaded may matter.
     * @return names of shared libraries to be loaded (e.g. "SDL2", "main").
     */
     
     // Actually, it *is* overridden because we generate .so files manually
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            // "SDL2_image",
            // "SDL2_mixer",
            // "SDL2_net",
            // "SDL2_ttf",
            "main"
        };
    }
}

