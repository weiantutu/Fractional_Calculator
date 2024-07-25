void QuickSort(int left, int right)
{
   int i = left, j = right, temp;
   // 若left >= right,则说明数组中只有一个元素或为空,无需排序
   if (left >= right)
       return;
   // 选择第left个元素作为基准
   temp = arr[left];
   while (i != j)
   {
       // 从右边开始找比基准小的元素
       while (arr[j] >= temp && i < j)
           j--;
       // 从左边开始找比基准大的元素
       while (arr[i] <= temp && i < j)
           i++;
       // 交换i和j指向的元素
       if (i < j)
       {
           int t = arr[i];
           arr[i] = arr[j];
           arr[j] = t;
       }
   }
   // 经过上述循环后,i=j,将基准元素归位
   arr[left] = arr[i];
   arr[i] = temp;
   // 递归左右两边
   quickSort(left, i - 1);
   quickSort(i + 1, right);
   return;
}
