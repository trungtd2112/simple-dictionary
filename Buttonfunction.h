#include "btree.h"
#include"handle.h"
#include<ctype.h>
GtkWidget *view, *searchEntry, *searchEntry, *label, *labelD, *meaningTextView;
GtkWidget *addWordEntry, *addMeaningEntry, *addUpdateButton;
GtkWidget *editSearchEntry, *editSearchButton, *editMeaningEntry, *editUpdateButton;
GtkWidget *deleteSearchEntry, *deleteSearchButton, *deleteMeaningEntry;
char word[1000], data[1000];
GtkTextBuffer *buffer;
GtkTextIter iter;
BTA *Dic, *SoundexCode_Tree;

gchar *chaoMung = "", *them = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________________________";


static void enter_callback(GtkWidget *widget, GtkWidget *entry){
	const gchar *entry_text;
	entry_text = gtk_entry_get_text(GTK_ENTRY(searchEntry));
	gtk_entry_set_text(GTK_ENTRY(meaningTextView), entry_text);
}
static void enter_callback2(GtkWidget *widget, GtkWidget *entry){
	char *e;
	int k;
	char result[100];
	e = (char*)gtk_entry_get_text(GTK_ENTRY(searchEntry));
	k = CompleteWord(SoundexCode_Tree, e, result);
	if (k != 0)
		gtk_entry_set_text(GTK_ENTRY(searchEntry), result);
}

static void addTab(GtkButton *button, GtkNotebook *notebook){
	gint page;
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1);
}
int checkEdibleString(char *str){
	if (strlen(str) == 0)	 return 0;
	for(int i = 0; i < strlen(str); i++){
		if (!isalpha(str[i]) && !isdigit(str[i]) && !(str[i] == '-') && !(str[i] == '\'') && !(str[i] == ' '))  return 0;
	}
	return 1;
}
static void suggestFunction(GtkButton *button, GtkNotebook *notebook){
	char suggest[100][100];
	char *e;
	int k, i, j = 0;
	e = (char*)gtk_entry_get_text(GTK_ENTRY(searchEntry));
	if (gtk_entry_get_text_length(GTK_ENTRY(searchEntry)) > 0){
		k = SuggestWord(SoundexCode_Tree, e, suggest);
		if (k != 0){
			char tmp[1000];
			strcpy(tmp, "\n----------------------------------\nDO YOU MEAN ??\n");;
			for (j = 0; j < 10; j++){
				if (checkEdibleString(suggest[j])){
					strcat(tmp, suggest[j]);
					strcat(tmp, "\n"); i++;
				}
				else	continue;
			}
			if (i == 0){
				strcpy(tmp, "*Oops!! We have no idea about this word");
				strcat(tmp, them);
				gtk_text_buffer_set_text(buffer, tmp, -1);
			}
			else {
				strcat(tmp, them);
				gtk_text_buffer_set_text(buffer, tmp, -1);
			}
		}
	}
}
static void searchMainFunction(GtkButton *button, GtkNotebook *notebook){
	gint page;
	page = gtk_notebook_get_current_page(notebook);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
	char *get_word;
	if (gtk_entry_get_text_length(GTK_ENTRY(searchEntry)) > 0){
		get_word = (char*)gtk_entry_get_text(GTK_ENTRY(searchEntry));
		int j;
		int k = btsel(Dic, get_word, data, sizeof(data), &j);
		if (k == 0){
			strcat(data, them);
			gtk_text_buffer_set_text(buffer, data, -1);
		}
	}
	else
		gtk_text_buffer_set_text(buffer, them, -1);
}

static void editSearchFunction(GtkButton *button, GtkNotebook *notebook ){
    const gchar *entry_text;
    char *get_word;
    get_word = (char*) gtk_entry_get_text (GTK_ENTRY (editSearchEntry));
    int real_size;
    int k = btsel(Dic, get_word, data, sizeof(data), &real_size);
    if(k != 0) 
		gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),"*Non-existent Word");
    else {
        gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),data);
    }
}

static void editUpdateFunction(GtkButton *button, GtkNotebook *notebook){
	char *get_word, *get_mean;
	get_word = (char*)gtk_entry_get_text(GTK_ENTRY(editSearchEntry));
	get_mean = (char*)gtk_entry_get_text(GTK_ENTRY(editMeaningEntry));
	int k = btupd(Dic, get_word, get_mean, sizeof(data));
	if (k != 0)
		gtk_entry_set_text(GTK_ENTRY(editMeaningEntry), "*Unsuccessfully Edited");
	else
		gtk_entry_set_text(GTK_ENTRY(editMeaningEntry), "*Successfully Edited");

	gtk_entry_set_text(GTK_ENTRY(editSearchEntry), " ");
}


static void deleteUpdateFunction( GtkButton   *button,GtkNotebook *notebook )
{
	char *get_word;
   	get_word = (char*) gtk_entry_get_text (GTK_ENTRY (deleteSearchEntry));
    btdel(SoundexCode_Tree, get_word);
    int k = btdel(Dic,get_word);
  	if(k != 0) gtk_entry_set_text (GTK_ENTRY(deleteMeaningEntry),"*Unsuccessfully Deleted");
  	else gtk_entry_set_text (GTK_ENTRY(deleteMeaningEntry),"*Successfully Deleted");
  	gtk_entry_set_text (GTK_ENTRY(deleteSearchEntry)," ");

}


static void editTab(GtkButton *button, GtkNotebook *notebook){
	gint page;
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 2);
}


static void addUpdate(GtkButton *button, GtkNotebook *notebook){
	char *get_word, *get_mean;
	get_word = (char*)gtk_entry_get_text(GTK_ENTRY(addWordEntry));
	get_mean = (char*)gtk_entry_get_text(GTK_ENTRY(addMeaningEntry));
	if(bfndky(Dic, get_word, get_mean) == 0) gtk_entry_set_text(GTK_ENTRY(addMeaningEntry), "*Existing Word");
	else{
		int k = btins(Dic, get_word, get_mean, sizeof(data));
		if (k == 0){
			gtk_entry_set_text(GTK_ENTRY(addMeaningEntry), "*Successfully Added");
			char code[5];
			SoundEx(code, get_word, 4, 1);
			btins(SoundexCode_Tree, get_word, code, 5 * sizeof(char));
		}
	}
	gtk_entry_set_text(GTK_ENTRY(addWordEntry), " ");
}

static void deleteTab(GtkButton *button, GtkNotebook *notebook){
	gint page;
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 3);
}


static GtkWidget *xpm_label_box(gchar *xpm_filename, gchar *label_text){
	GtkWidget *box, *label, *image;

	box = gtk_box_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 2);
	image = gtk_image_new_from_file(xpm_filename);
	label = gtk_label_new(label_text);
	
	gtk_box_pack_start(GTK_BOX(box), image, 0, 0, 3);
	gtk_box_pack_start(GTK_BOX(box), label, 0, 0, 3);

	gtk_widget_show(image);
	gtk_widget_show(label);

    return box;
}
static GtkWidget *xpm_label_box2(gchar *xpm_filename){
    GtkWidget *box, *image;

    box = gtk_box_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER (box), 2);
    image = gtk_image_new_from_file(xpm_filename);
    gtk_box_pack_start(GTK_BOX (box), image, 0, 0, 3);
    
	gtk_widget_show(image);

    return box;
}
