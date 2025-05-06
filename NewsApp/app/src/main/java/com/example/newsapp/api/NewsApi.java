package com.example.newsapp.api;

import com.example.newsapp.model.NewsResponse;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Header;
import retrofit2.http.Query;

public interface NewsApi {
    @GET("v2/top-headlines")
    Call<NewsResponse> getTopHeadlines(
            @Header("User-Agent") String userAgent,
            @Query("country") String country,
            @Query("apiKey") String apiKey,
            @Query("pageSize") int pageSize
    );
}