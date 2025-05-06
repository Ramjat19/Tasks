package com.example.newsapp.model;

import com.google.gson.annotations.SerializedName;

public class Source {
    @SerializedName("id")
    private String id;

    @SerializedName("name")
    private String name;

    // Getters
    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}