package com.example.newsapp;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;
import com.example.newsapp.adapter.NewsAdapter;
import com.example.newsapp.api.NewsApi;
import com.example.newsapp.model.Article;
import com.example.newsapp.model.NewsResponse;

import java.util.List;
import java.io.IOException;
import java.util.ArrayList;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class MainActivity extends AppCompatActivity implements NewsAdapter.OnItemClickListener {
    private static final String BASE_URL = "https://newsapi.org/";
    private static final String API_KEY = "1478806855f942e69174b855529055ac";
    private static final String COUNTRY = "us";
    private static final int PAGE_SIZE = 20;

    private RecyclerView newsRecyclerView;
    private NewsAdapter newsAdapter;
    private ProgressBar progressBar;
    private SwipeRefreshLayout swipeRefreshLayout;
    private NewsApi newsApi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize views
        newsRecyclerView = findViewById(R.id.newsRecyclerView);
        progressBar = findViewById(R.id.progressBar);
        swipeRefreshLayout = findViewById(R.id.swipeRefreshLayout);

        // Setup RecyclerView
        newsRecyclerView.setLayoutManager(new LinearLayoutManager(this));
        newsAdapter = new NewsAdapter(this);  // Updated this line
        newsRecyclerView.setAdapter(newsAdapter);

        // Setup SwipeRefreshLayout
        swipeRefreshLayout.setOnRefreshListener(this::fetchNews);

        // Setup Retrofit
        HttpLoggingInterceptor logging = new HttpLoggingInterceptor();
        logging.setLevel(HttpLoggingInterceptor.Level.BODY);

        OkHttpClient client = new OkHttpClient.Builder()
                .addInterceptor(logging)
                .build();

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BASE_URL)
                .client(client)
                .addConverterFactory(GsonConverterFactory.create())
                .build();

        newsApi = retrofit.create(NewsApi.class);

        // Fetch news
        fetchNews();
    }

    private void fetchNews() {
        Log.d("NewsApp", "Starting news fetch...");
        progressBar.setVisibility(View.VISIBLE);

        String userAgent = "NewsApp/1.0";
        newsApi.getTopHeadlines(userAgent, COUNTRY, API_KEY, PAGE_SIZE)
                .enqueue(new Callback<NewsResponse>() {
                    @Override
                    public void onResponse(Call<NewsResponse> call, Response<NewsResponse> response) {
                        progressBar.setVisibility(View.GONE);
                        swipeRefreshLayout.setRefreshing(false);

                        if (response.isSuccessful() && response.body() != null) {
                            List<Article> articles = response.body().getArticles();
                            Log.d("NewsApp", "Success! Articles count: " + articles.size());

                            if (articles.isEmpty()) {
                                Toast.makeText(MainActivity.this,
                                        "No articles found. Try a different category or country.",
                                        Toast.LENGTH_LONG).show();
                            } else {
                                newsAdapter.updateArticles(articles);
                            }
                        } else {
                            String errorBody = "";
                            try {
                                if (response.errorBody() != null) {
                                    errorBody = response.errorBody().string();
                                }
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

                            Log.e("NewsApp", "Error Response Code: " + response.code());
                            Log.e("NewsApp", "Error Body: " + errorBody);

                            String errorMessage = "Error: " + response.code();
                            if (!errorBody.isEmpty()) {
                                errorMessage += " - " + errorBody;
                            }
                            Toast.makeText(MainActivity.this, errorMessage, Toast.LENGTH_LONG).show();
                        }
                    }

                    @Override
                    public void onFailure(Call<NewsResponse> call, Throwable t) {
                        progressBar.setVisibility(View.GONE);
                        swipeRefreshLayout.setRefreshing(false);
                        Log.e("NewsApp", "Network Error", t);
                        Toast.makeText(MainActivity.this, "Error: " + t.getMessage(), Toast.LENGTH_LONG).show();
                    }
                });
    }

    @Override
    public void onItemClick(Article article) {
        // Handle article click - open in browser
        if (article.getUrl() != null && !article.getUrl().isEmpty()) {
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(article.getUrl()));
            startActivity(intent);
        }
    }
}