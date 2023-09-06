#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enums
enum Genre {
    ROCK,
    POP,
    HIP_HOP,
    JAZZ,
    OTHER
};

// Structures
struct Track {
    char name[100];
    char fileLocation[200];
};

struct Album {
    char artist[100];
    char albumName[100];
    enum Genre genre;
    int numTracks;
    struct Track tracks[20]; // Maximum 20 tracks per album
};

// Function prototypes
void printMenu();
void addAlbum(struct Album albums[], int *numAlbums);
void listAlbums(struct Album albums[], int numAlbums);
void playMusic(struct Album albums[], int numAlbums);


//Initializes an array of Album structures to store album information (up to 50 albums)

int main() {
    struct Album albums[50]; // Maximum 50 albums
    int numAlbums = 0;
    int choice;


    //Continuously display a menu and wait for user input
    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAlbum(albums, &numAlbums);
                break;
            case 2:
                listAlbums(albums, numAlbums);
                break;
            case 3:
                playMusic(albums, numAlbums);
                break;
            case 4:
                printf("Exiting music player. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Prints the menu options to the console.
void printMenu() {
    printf("\nMusic Player Menu\n");
    printf("1. Add Album\n");
    printf("2. List Albums\n");
    printf("3. Play Music\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

//Allows the user to input album information
void addAlbum(struct Album albums[], int *numAlbums) {
    //Validates that the maximum number of albums 
    if (*numAlbums >= 50) {
        printf("Maximum number of albums reached.\n");
        return;
    }

    struct Album *newAlbum = &albums[*numAlbums];
    printf("Enter artist name: ");
    scanf("%s", newAlbum->artist);
    printf("Enter album name: ");
    scanf("%s", newAlbum->albumName);
    printf("Enter genre (0-4: ROCK, POP, HIP_HOP, JAZZ, OTHER): ");
    int genreChoice;
    scanf("%d", &genreChoice);
    newAlbum->genre = (enum Genre)genreChoice;

    printf("Enter number of tracks: ");
    scanf("%d", &newAlbum->numTracks);
    for (int i = 0; i < newAlbum->numTracks; i++) {
        printf("Enter track %d name: ", i + 1);
        scanf("%s", newAlbum->tracks[i].name);
        printf("Enter track %d file location: ", i + 1);
        scanf("%s", newAlbum->tracks[i].fileLocation);
    }

    (*numAlbums)++;
}

//Displays a list of albums along with their details

void listAlbums(struct Album albums[], int numAlbums) {
    printf("\nAlbums:\n");
    for (int i = 0; i < numAlbums; i++) {
        printf("Album %d:\n", i + 1);
        printf("Artist: %s\n", albums[i].artist);
        printf("Album Name: %s\n", albums[i].albumName);
        printf("Genre: %d\n", albums[i].genre);
        printf("Number of Tracks: %d\n", albums[i].numTracks);
        printf("Tracks:\n");
        for (int j = 0; j < albums[i].numTracks; j++) {
            printf("  %d. %s - %s\n", j + 1, albums[i].tracks[j].name, albums[i].tracks[j].fileLocation);
        }
        printf("\n");
    }
}

//Allows the user to select an album and a track to play.

void playMusic(struct Album albums[], int numAlbums) {
    int albumIndex, trackIndex;
    
    printf("\nSelect an album to play from:\n");
    for (int i = 0; i < numAlbums; i++) {
        printf("%d. %s - %s\n", i + 1, albums[i].artist, albums[i].albumName);
    }
    
    printf("Enter the album number: ");
    scanf("%d", &albumIndex);
    albumIndex--; // Adjust for zero-based index
    
    if (albumIndex >= 0 && albumIndex < numAlbums) {
        struct Album selectedAlbum = albums[albumIndex];
        
        printf("\nSelect a track to play from the album '%s':\n", selectedAlbum.albumName);
        for (int i = 0; i < selectedAlbum.numTracks; i++) {
            printf("%d. %s\n", i + 1, selectedAlbum.tracks[i].name);
        }
        
        printf("Enter the track number: ");
        scanf("%d", &trackIndex);
        trackIndex--; // Adjust for zero-based index
        
        if (trackIndex >= 0 && trackIndex < selectedAlbum.numTracks) {
            char command[256];
            snprintf(command, sizeof(command), "mpg123 \"%s\"", selectedAlbum.tracks[trackIndex].fileLocation);
            
            printf("Playing '%s - %s'...\n", selectedAlbum.tracks[trackIndex].name, selectedAlbum.artist);
            system(command);
        } else {
            printf("Invalid track number.\n");
        }
    } else {
        printf("Invalid album number.\n");
    }
}
