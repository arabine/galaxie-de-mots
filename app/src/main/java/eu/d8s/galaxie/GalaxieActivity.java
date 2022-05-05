 
package eu.d8s.galaxie;

import org.libsdl.app.SDLActivity;

import java.io.File;
import java.io.IOException;
import android.os.Bundle;
import android.util.Log;
/* 
 * A sample wrapper class that just calls SDLActivity 
 */ 

public class GalaxieActivity extends SDLActivity
{
    private final static String TAG = "GalaxieActivity";
    DatabaseHelper dbHelper = null;

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

