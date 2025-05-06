package com.example.newsapp.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.engine.DiskCacheStrategy;
import com.bumptech.glide.request.RequestOptions;
import com.example.newsapp.R;
import com.example.newsapp.model.Article;

import java.util.ArrayList;
import java.util.List;

public class NewsAdapter extends RecyclerView.Adapter<NewsAdapter.NewsViewHolder> {
    private List<Article> articles;
    private final OnItemClickListener listener;

    // Interface for click events
    public interface OnItemClickListener {
        void onItemClick(Article article);
    }

    // Constructor
    public NewsAdapter(OnItemClickListener listener) {
        this.articles = new ArrayList<>();
        this.listener = listener;
    }

    @NonNull
    @Override
    public NewsViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_news, parent, false);
        return new NewsViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull NewsViewHolder holder, int position) {
        Article article = articles.get(position);

        // Configure Glide options
        RequestOptions requestOptions = new RequestOptions()
                .placeholder(R.drawable.placeholder_image)
                .error(R.drawable.error_image)
                .diskCacheStrategy(DiskCacheStrategy.ALL)
                .centerCrop();

        // Load image with Glide
        if (article.getUrlToImage() != null && !article.getUrlToImage().isEmpty()) {
            Glide.with(holder.itemView.getContext())
                    .load(article.getUrlToImage())
                    .apply(requestOptions)
                    .into(holder.newsImageView);
        } else {
            // If no image URL, show placeholder
            holder.newsImageView.setImageResource(R.drawable.placeholder_image);
        }

        // Set text content
        holder.titleTextView.setText(article.getTitle());
        holder.descriptionTextView.setText(article.getDescription());

        // Set source name if available
        if (article.getSource() != null && article.getSource().getName() != null) {
            holder.sourceTextView.setText(article.getSource().getName());
        } else {
            holder.sourceTextView.setText(R.string.unknown_source);
        }

        // Set click listener
        holder.itemView.setOnClickListener(v -> {
            if (listener != null) {
                listener.onItemClick(article);
            }
        });
    }

    @Override
    public int getItemCount() {
        return articles != null ? articles.size() : 0;
    }

    // Method to update articles
    public void updateArticles(List<Article> newArticles) {
        if (newArticles != null) {
            this.articles = newArticles;
            notifyDataSetChanged();
        }
    }

    // ViewHolder class
    static class NewsViewHolder extends RecyclerView.ViewHolder {
        final ImageView newsImageView;
        final TextView titleTextView;
        final TextView descriptionTextView;
        final TextView sourceTextView;

        NewsViewHolder(@NonNull View itemView) {
            super(itemView);
            newsImageView = itemView.findViewById(R.id.newsImageView);
            titleTextView = itemView.findViewById(R.id.titleTextView);
            descriptionTextView = itemView.findViewById(R.id.descriptionTextView);
            sourceTextView = itemView.findViewById(R.id.sourceTextView);
        }
    }
}