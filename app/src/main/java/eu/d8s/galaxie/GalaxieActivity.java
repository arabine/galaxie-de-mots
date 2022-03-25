 
package eu.d8s.galaxie;

import org.libsdl.app.SDLActivity; 

/* 
 * A sample wrapper class that just calls SDLActivity 
 */ 

public class GalaxieActivity extends SDLActivity
{


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

