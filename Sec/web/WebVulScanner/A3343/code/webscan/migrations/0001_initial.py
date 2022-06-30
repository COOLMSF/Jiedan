# Generated by Django 3.1.4 on 2021-01-02 07:11

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Category',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=20, verbose_name='名称')),
                ('sort', models.IntegerField(default=1, verbose_name='排序')),
                ('add_menu', models.BooleanField(default=True, verbose_name='添加到导航栏')),
                ('icon', models.CharField(default='fas fa-home', max_length=30, verbose_name='图标')),
            ],
            options={
                'verbose_name': '分类',
                'verbose_name_plural': '分类',
            },
        ),
        migrations.CreateModel(
            name='Item',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=10, verbose_name='标题')),
                ('desc', models.TextField(max_length=50, verbose_name='描述')),
                ('url', models.URLField(blank=True, verbose_name='网址')),
                ('img', models.URLField(default='https://jwt1399.top/favicon.png', verbose_name='图片')),
                ('category', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='webscan.category', verbose_name='分类')),
            ],
            options={
                'verbose_name': '导航条目',
                'verbose_name_plural': '导航条目',
            },
        ),
    ]