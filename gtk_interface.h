// Refactor 10:21pm 9/5 by Thao

#include"Buttonfunction.h"
#include"xulyFile.h"

void inital(int argc, char **argv){
	int i;
	GtkWidget *layout1, *label2, *label3, *labelD;
    GtkWidget *window, *layout, *layoutbox, *comboBox, *titleBox, *newBox, *editBox, *deleteBox, *notebook;    
    GtkWidget *deleteButton, *searchButton, *newButton, *editButton, *titleButton;    
	char bufferf[32], bufferf2[32], bufferf3[32], bufferl[32];
	gchar* moreSpace = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________________________";
	
	gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_container_set_resize_mode(GTK_CONTAINER (window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 800);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout);
    layoutbox = xpm_label_box2("background.jpg");
    gtk_container_add(GTK_CONTAINER(layout), layoutbox);
    gtk_widget_show(layout);
    gtk_widget_show(layoutbox);

    notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
	gtk_widget_show(notebook);

    for (i = 0; i < 4; i++){
		layout1 = gtk_layout_new(NULL, NULL);
        gtk_widget_show(layout1);
		gtk_widget_set_size_request(layout1, 100, 75);
        if(i == 0){ //word detail notebook tab layout
			sprintf(bufferl, "Word detail");
			meaningTextView = gtk_text_view_new();
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(meaningTextView));
			gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
			char tmp[1000];
			strcpy(tmp, "Hello man ^_^");
			strcat(tmp, moreSpace);
			gtk_text_buffer_set_text(buffer, tmp, -1);
			gtk_layout_put(GTK_LAYOUT(layout1), meaningTextView, 0, 0);
        }
	
        if(i == 1) { //add notebook tab layout
			sprintf(bufferl, "New");

            addWordEntry=gtk_entry_new();
			gtk_entry_set_placeholder_text(GTK_ENTRY(addWordEntry), "Enter new word here");
            gtk_layout_put(GTK_LAYOUT(layout1), addWordEntry, 130, 48);

            addMeaningEntry=gtk_entry_new();
			gtk_entry_set_placeholder_text(GTK_ENTRY(addMeaningEntry), "Enter new meaning here");
			g_signal_connect(addMeaningEntry, "activate", G_CALLBACK(addUpdate), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), addMeaningEntry, 130, 88);

            addUpdateButton = gtk_button_new_with_label("Add");
			gtk_widget_set_size_request(addUpdateButton, 65, 70);
			g_signal_connect(addUpdateButton, "clicked", G_CALLBACK(addUpdate), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), addUpdateButton, 300, 50);

            label2 = gtk_label_new("Word");
			gtk_layout_put(GTK_LAYOUT(layout1), label2, 40, 50);
            gtk_widget_show(label2);

			label3 = gtk_label_new("Meaning");
			gtk_layout_put(GTK_LAYOUT(layout1), label3, 40, 90);
			gtk_widget_show(label3);
        }
		if (i == 2){ //edit notebook tab layout
            sprintf(bufferl, "Edit");

            editSearchEntry = gtk_entry_new();
			gtk_entry_set_placeholder_text(GTK_ENTRY(editSearchEntry), "Enter editing word here");
			g_signal_connect(editSearchEntry, "activate", G_CALLBACK(editSearchFunction), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), editSearchEntry, 130, 48);

			editSearchButton = gtk_button_new_with_label("Search");
			g_signal_connect(editSearchButton, "clicked", G_CALLBACK(editSearchFunction), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), editSearchButton, 300, 48);
            
			editMeaningEntry = gtk_entry_new();
			gtk_widget_set_size_request(editMeaningEntry, 300, 30);
			gtk_entry_set_placeholder_text(GTK_ENTRY(editMeaningEntry), "Enter new meaning here");
			g_signal_connect(editMeaningEntry, "activate", G_CALLBACK(editUpdateFunction), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), editMeaningEntry, 130, 88);

			editUpdateButton = gtk_button_new_with_label("Done");
			gtk_widget_set_size_request(editUpdateButton, 150, 50);
			g_signal_connect(editUpdateButton, "clicked", G_CALLBACK(editUpdateFunction), notebook);
			gtk_layout_put(GTK_LAYOUT(layout1), editUpdateButton, 180, 150);

			label3 = gtk_label_new("Meaning");
			gtk_layout_put(GTK_LAYOUT(layout1), label3, 40, 90);
			gtk_widget_show(label3);
        }
        if(i == 3){ 
			sprintf (bufferf, "Tìm từ");
            sprintf (bufferf2, " ");
            sprintf (bufferf3, "kết quả");
            sprintf (bufferl, "Delete");

            deleteSearchEntry=gtk_entry_new ();
            gtk_layout_put (GTK_LAYOUT(layout1),deleteSearchEntry,100,10);

            deleteSearchButton=gtk_button_new_with_label ("delete");
            g_signal_connect (deleteSearchButton, "clicked",G_CALLBACK (deleteUpdateFunction),notebook);
            gtk_layout_put (GTK_LAYOUT(layout1),deleteSearchButton,300,10);
            deleteMeaningEntry=gtk_entry_new ();
            gtk_layout_put (GTK_LAYOUT(layout1),deleteMeaningEntry,100,90);
            label2 = gtk_label_new (bufferf2);
        	gtk_layout_put (GTK_LAYOUT(layout1),label2,40,50);
        	gtk_widget_show (label2);

        	label3 = gtk_label_new (bufferf3);
        	gtk_layout_put (GTK_LAYOUT(layout1),label3,40,90);
        	gtk_widget_show (label3);
        	}
			label = gtk_label_new(bufferl);
			gtk_notebook_append_page(GTK_NOTEBOOK(notebook), layout1, label);
    }
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
	gtk_widget_set_size_request(notebook, 500, 550);
	gtk_layout_put(GTK_LAYOUT(layout), notebook, 30, 120);

    newButton = gtk_button_new();
	g_signal_connect(newButton, "clicked", G_CALLBACK(addTab), notebook);
    newBox = xpm_label_box("new.png", "New");
    gtk_widget_set_size_request(newButton, 115, 45);
    gtk_widget_show(newBox);
	gtk_container_add(GTK_CONTAINER(newButton), newBox);
	gtk_layout_put(GTK_LAYOUT(layout), newButton, 555, 200);

    editButton = gtk_button_new();
	g_signal_connect(editButton, "clicked", G_CALLBACK(editTab), notebook);
    editBox = xpm_label_box("edit.png", "Edit");
    gtk_widget_set_size_request(editButton, 115, 45);
    gtk_widget_show(editBox);
    gtk_container_add(GTK_CONTAINER(editButton), editBox);
	gtk_layout_put(GTK_LAYOUT(layout), editButton, 555, 300);

    deleteButton = gtk_button_new();
	g_signal_connect(deleteButton, "clicked", G_CALLBACK(deleteTab), notebook);
	deleteBox = xpm_label_box("delete.png", "Delete");
	gtk_widget_set_size_request(deleteButton, 115, 45);
    gtk_widget_show(deleteBox);
	gtk_container_add(GTK_CONTAINER(deleteButton), deleteBox);
	gtk_layout_put(GTK_LAYOUT(layout), deleteButton, 555, 400);

	searchButton = gtk_button_new_with_label("Search");
	g_signal_connect(searchButton, "clicked", G_CALLBACK(searchMainFunction), notebook);
	gtk_layout_put(GTK_LAYOUT(layout), searchButton, 400, 60);

	searchEntry = gtk_search_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(searchEntry), "Let's start");
	gtk_widget_set_size_request(searchEntry, 250, 30);
	g_signal_connect((gpointer)searchEntry, "focus", G_CALLBACK(enter_callback2), NULL);
	gtk_layout_put(GTK_LAYOUT(layout), searchEntry, 150, 60);
	g_signal_connect(searchEntry, "search-changed", G_CALLBACK(suggestFunction), notebook);

	gtk_widget_show_all(window);

    btinit();
	Dic = btopn("data", 0, 0);
    if(!Dic){
		printf("Creating data...\n");
		Create_BT(&Dic);
    } 
	SoundexCode_Tree = btopn("soundexTree", 0, 0);
    if(!SoundexCode_Tree){
		printf("Creating SoundexTree...\n");
		SoundexCode_of_Dic(Dic, &SoundexCode_Tree);
    }
	gtk_main();
}
